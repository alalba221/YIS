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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "yspch.h"
	pchsource "Yis/src/yspch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	defines
	{
		"YS_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{prj.name}/vendor/assimp/include"
	}
	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"YS_PLATFORM_WINDOWS",
			"YS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "YS_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "YS_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "YS_Dist"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	defines
	{
		"YS_PLATFORM_WINDOWS"
	}
	includedirs
	{
		"Yis/vendor/spdlog/include",
		"Yis/src",
		"Yis/vendor",
		"%{IncludeDir.glm}"

	}
	links
	{
		"Yis",
		"Yis/vendor/assimp/win64/assimp.lib"
	}
	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"YS_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines "YS_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "YS_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "YS_Dist"
		runtime "Release"
		optimize "on"





