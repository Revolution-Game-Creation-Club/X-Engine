workspace "XEngine"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "XEngine"
	location "XEngine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/src", "%{prj.name}/vendor/spdlog/include" }
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS", "X_BUILD_DLL" }
		postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/RainfallCity") }
	filter "configurations:Debug"
		defines "X_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "X_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "X_DIST"
		optimize "On"
project "RainfallCity"
	location "RainfallCity"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/src", "XEngine/vendor/spdlog/include", "XEngine/src"}
	links { "XEngine" }
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { "X_PLATFORM_WINDOWS" }
	filter "configurations:Debug"
		defines "X_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "X_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "X_DIST"
		optimize "On"
