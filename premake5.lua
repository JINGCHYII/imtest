workspace "Imter"
    architecture "x64"
    targetdir "build"

    configurations
    {
		"Debug",
        "Release"
    }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "Imter/vendor/glfw/include"
IncludeDir["glad"] = "Imter/vendor/glad/include"
IncludeDir["glm"] = "Imter/vendor/glm"
IncludeDir["imgui"] = "Imter/vendor/imGui"

project "Imter"
    location "Imter"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
 
	targetdir ("bin/" .. outputdir .. "-%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "-%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/assets/ImterContents/**.h"
    }
	
	includedirs
	{
		"%{prj.name}/assets",
		"%{prj.name}/src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{prj.name}/vendor",
		"%{prj.name}/vendor/stb_image",
		"%{prj.name}/vendor/mysql/include",
		"%{prj.name}/vendor/pylib/include",
		"%{prj.name}/vendor/jsoncpp/include"
	}
	
	libdirs
	{
		"%{prj.name}/vendor/glfw/lib",
		"%{prj.name}/vendor/glad/lib",
		"%{prj.name}/vendor/imgui/lib",
		"%{prj.name}/vendor/mysql/lib",
		"%{prj.name}/vendor/pylib/lib",
		"%{prj.name}/vendor/assimp/lib"
	}
	
	links 
	{ 
		"GLFW.lib",
		"glad.lib",
		"imgui.lib",
		"python39.lib",
		"libmysql.lib",
		"jsoncpp.lib",
		"assimp.lib"
	}

    filter "system:windows"
        systemversion "latest"
		
		defines 
		{ 
		}
		
		postbuildcommands 
		{
			'{COPY} "%{prj.location}/vendor/assimp/lib/assimp-vc140-mt.dll" "%{cfg.targetdir}"',
			'{COPY} "%{prj.location}/assets/" "%{cfg.targetdir}/assets/"'
		}
		
	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "on"
		
		libdirs
		{
			"%{prj.name}/vendor/jsoncpp/lib/Debug"
		}
		
		links 
		{
			"python39_d.lib"
		}		
		
		postbuildcommands 
		{
			'{COPY} "%{prj.location}/vendor/pylib/lib/python39_d.dll" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MD"
		optimize "on"
		
		libdirs
		{
			"%{prj.name}/vendor/jsoncpp/lib/Release"
		}
		
		links 
		{
			"python39.lib"
		}	
		
		postbuildcommands 
		{
			'{COPY} "%{prj.location}/vendor/pylib/lib/python39.dll" "%{cfg.targetdir}"'
		}