/*****************************************************************************
 Emp
 
 Copyright (C) 2017  German Molina (germolinal@gmail.com)
 
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

// Include materials

#include "../ghm_commands/materials/dielectric.h"
#include "../ghm_commands/materials/glass.h"
#include "../ghm_commands/materials/glow.h"
#include "../ghm_commands/materials/interface.h"
#include "../ghm_commands/materials/light.h"
#include "../ghm_commands/materials/metal.h"
#include "../ghm_commands/materials/plastic.h"
#include "../ghm_commands/materials/spotlight.h"
#include "../ghm_commands/materials/trans.h"


#define ADD_MATERIAL(X) X * m = new X(&name); \
fillData(m,L,1); \
model->addMaterial(m); \
lua_pushstring(L,m->getType()->c_str()); \


int createMaterial(lua_State * L, const char * type)
{
    
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check type
    checkArgType(L, LUA_TTABLE, 1);
    
    // Identify name
    std::string name = getNameFromTable(L,1);
    
    // Get the current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Create the object and fill it
    if(strcmp(type,"dielectric") == 0){
        ADD_MATERIAL(Dielectric);        
    }else if(strcmp(type,"glass") == 0){
        ADD_MATERIAL(Glass);        
    }else if(strcmp(type,"glow") == 0){
        ADD_MATERIAL(Glow);        
    }else if(strcmp(type,"interface") == 0){
        ADD_MATERIAL(Interface);        
    }else if(strcmp(type,"light") == 0){
        ADD_MATERIAL(Light);        
    }else if(strcmp(type,"metal") == 0){
        ADD_MATERIAL(Metal);        
    }else if(strcmp(type,"plastic") == 0){
        ADD_MATERIAL(Plastic);        
    }else if(strcmp(type,"spotlight") == 0){
        ADD_MATERIAL(Spotlight);        
    }else if(strcmp(type,"trans") == 0){
        ADD_MATERIAL(Trans);        
    }else{
        std::string e = "Unknown Material type '"+std::string(type)+"'";
        sendError(L,"Fatal", &e[0]);
    }
    
    // But add Class to the original table
    lua_setfield(L,1,"class");
        
    // Return the name
    lua_pushstring(L,name.c_str());
    
    // and the table
    lua_pushvalue(L,1);
    
    int tableIndex = lua_gettop(L);
    
    // Add the name to the original table
    lua_pushstring(L,name.c_str());
    lua_setfield(L,tableIndex,"name");
    
    return 2;
}

#undef ADD_MATERIAL
