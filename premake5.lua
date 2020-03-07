workspace "XEngine"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "XEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "XEngine/vendor/GLAD/include"
include "XEngine/vendor/GLFW"
include "XEngine/vendor/GLAD"
project "XEngine"
	location "XEngine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	pchheader "Xpch.h"
	pchsource "XEngine/src/Xpch.cpp"
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/src", "%{prj.name}/vendor/spdlog/include", "%{IncludeDir.GLFW}", "%{IncludeDir.GLAD}" }
	links{ "GLFW", "GLAD", "opengl32.lib" }
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS", "X_BUILD_DLL", "GLFW_INCLUDE_NONE" }
		postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Game") }
	filter "configurations:Debug"
		defines "X_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "X_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "X_DIST"
		buildoptions "/MD"
		optimize "On"
project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/src", "XEngine/vendor/spdlog/include", "XEngine/src" }
	links { "XEngine" }
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS" }
	filter "configurations:Debug"
		defines "X_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "X_RELEASE"
		buildoptions "/MD"
		optimize "On"
	filter "configurations:Dist"
		defines "X_DIST"
		buildoptions "/MD"
		optimize "On"