/*****************************************************************************
 Emp
 
 Copyright (C) 2018  German Molina (germolinal@gmail.com)
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 *****************************************************************************/

#include "./common.h"
#include "./create_otype.h"
#include "./get_layer.h"
#include "./get_material.h"

// Include otypes
#include "../commands/model/otypes/bubble.h"
#include "../commands/model/otypes/cone.h"
#include "../commands/model/otypes/cup.h"
#include "../commands/model/otypes/cylinder.h"
#include "../commands/model/otypes/face.h"
#include "../commands/model/otypes/ring.h"
#include "../commands/model/otypes/source.h"
#include "../commands/model/otypes/sphere.h"
#include "../commands/model/otypes/tube.h"


#define ADD_OBJECT(X) X * o = new X(&name); \
fillData(o,L,1); \
layer->addObject(o); \
std::string type = o->getType(); \
lua_pushstring(L,&type[0]); \
if(material != nullptr) \
o->setMaterial(material)
               


int createOtype(lua_State * L, const char * type)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check type
    checkArgType(L, LUA_TTABLE, 1);
    
    // Idenfity a Layer
    Layer * layer = getLayerAccordingToTable(L,1);
    
    // Identify name
    std::string name = getNameFromTable(L,1);
    
    // Identify material
    std::string materialName;
    Material * material = nullptr;
    if(fieldExists(L,1, "material")){
        materialName = getStringFromTableField(L, 1, "material");
        material = getMaterial(L,&materialName);
    }
    
    // Create the object and fill it
    if(strcmp(type,"bubble") == 0){
        ADD_OBJECT(Bubble);
    }else if(strcmp(type,"cone") == 0){
        ADD_OBJECT(Cone);
    }else if(strcmp(type,"cup") == 0){        
        ADD_OBJECT(Cup);        
    }else if(strcmp(type,"cylinder") == 0){        
        ADD_OBJECT(Cylinder);         
    }else if(strcmp(type,"polygon") == 0){
        ADD_OBJECT(Face);        
    }else if(strcmp(type,"ring") == 0){
        ADD_OBJECT(Ring);
    }else if(strcmp(type,"source") == 0){
        ADD_OBJECT(Source);
    }else if(strcmp(type,"sphere") == 0){
        ADD_OBJECT(Sphere);
    }else if(strcmp(type,"tube") == 0){
        ADD_OBJECT(Tube);
    }else{
        std::string e = "Unknown Otype '"+std::string(type)+"'";
        sendError(L,"Fatal", &e[0]);
    }
    
    // Add Class to the original table
    lua_setfield(L,1,"class");
    
    // Add the layer to the original table
    std::string layerName = layer->getName();
    lua_pushstring(L,&layerName[0]);
    lua_setfield(L,1,"layer");
    
    // Add the name to the original table
    lua_pushstring(L,name.c_str());
    lua_setfield(L,1,"name");
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    // Return the name
    lua_pushstring(L,name.c_str());
    
    // and the table
    lua_pushvalue(L,1);
    
    return 2;
}

#undef ADD_OBJECT
