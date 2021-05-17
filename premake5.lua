workspace "Yis"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relatice to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Yis/vendor/GLFW/include"
IncludeDir["Glad"] = "Yis/vendor/Glad/include"
IncludeDir["ImGui"] = "Yis/vendor/imgui"
startproject "Sandbox"

include "Yis/vendor/GLFW"
include "Yis/vendor/Glad"
include "Yis/vendor/imgui"

project "Yis"
	location "Yis"
	kind "SharedLib"
	language "C++"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "yspch.h"
	pchsource "Yis/src/yspch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}"
	}
	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"YS_PLATFORM_WINDOWS",
			"YS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/"..outputdir.."/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "YS_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "YS_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "YS_Dist"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"Yis/vendor/spdlog/include",
		"Yis/src"

	}
	links
	{
		"Yis"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"YS_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "YS_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "YS_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "YS_Dist"
		buildoptions "/MD"
		optimize "On"





