workspace "XEngine"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "XEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "XEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "XEngine/vendor/ImGui"
include "XEngine/vendor/GLFW"
include "XEngine/vendor/GLAD"
include "XEngine/vendor/ImGui"
startproject "Game"
project "XEngine"
	location "XEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	pchheader "Xpch.h"
	pchsource "XEngine/src/Xpch.cpp"
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/src", "%{prj.name}/vendor/spdlog/include", "%{IncludeDir.GLFW}", "%{IncludeDir.GLAD}", "%{IncludeDir.ImGui}" }
	links{ "GLFW", "GLAD", "ImGui", "opengl32.lib" }
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS", "X_BUILD_DLL", "GLFW_INCLUDE_NONE" }
		postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Game") }
	filter "configurations:Debug"
		defines "X_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "X_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "X_DIST"
		runtime "Release"
		optimize "On"
project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/src", "XEngine/vendor/spdlog/include", "XEngine/src" }
	links { "XEngine" }
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS" }
	filter "configurations:Debug"
		defines "X_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "X_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "X_DIST"
		runtime "Release"
		optimize "On"
