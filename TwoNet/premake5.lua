project "TwoNet"
	kind "StaticLib"
	language "C++"

	targetdir ("lib")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "include/TwoNet/pch.cpp" 

	files
	{
		"include/TwoNet/**.cpp",
		"include/TwoNet/**.h"
	}

	includedirs {
		"src"
	}

	defines { }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Debug"
		symbols "On"
	
