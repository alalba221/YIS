workspace "Yis"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
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
		symbols "On"
	filter "configurations:Release"
		defines "YS_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "YS_Dist"
		optimize "On"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"YS_PLATFORM_WINDOWS",
			"YS_BUILD_DLL"
		}
	postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
		}

	filter "configurations:Debug"
		defines "YS_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "YS_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "YS_Dist"
		optimize "On"

