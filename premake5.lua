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
IncludeDir["glm"] = "Yis/vendor/glm"
startproject "Sandbox"

group"Dependencies"
	include "Yis/vendor/GLFW"
	include "Yis/vendor/Glad"
	include "Yis/vendor/imgui"
group""

project "Yis"
	location "Yis"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "YS_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "YS_Dist"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "off"
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
		"Yis/src",
		"%{IncludeDir.glm}"

	}
	links
	{
		"Yis"
	}
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"YS_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "YS_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "YS_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "YS_Dist"
		runtime "Release"
		optimize "On"





