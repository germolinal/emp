-- premake5.lua


-- Run pre-build commands
premakescripts_dir = "./premakescripts"
dofile(premakescripts_dir.."/config.lua")
dofile(premakescripts_dir.."/prebuild.lua")


workspace "Emp"
    architecture "x86_64"
    configurations { "DEBUG", "RELEASE" } 
    defines { "EMP" }   

filter "configurations:DEBUG"
    symbols "On" 
    defines { 
        "_DEBUG", 
        "TBB_DO_ASSERT=1", 
        "TBB_DO_THREADING_TOOLS=1" 
    }

filter "configurations:RELEASE"
    optimize "On"
    defines { 
        "TBB_DO_ASSERT=0", 
        "TBB_DO_THREADING_TOOLS=0" 
    }

-- Fix to set Windows 10 instead of 8.1
if is_windows then
    systemversion(os.winSdkVersion() .. ".0")
end

dofile(premakescripts_dir.."/lua.lua")
dofile(premakescripts_dir.."/emp_core.lua")
dofile(premakescripts_dir.."/emp.lua")
dofile(premakescripts_dir.."/rtrad.lua")
  

--package.path = package.path .. ";"..premakescripts_dir.."/?.lua"
--require("tbb")
