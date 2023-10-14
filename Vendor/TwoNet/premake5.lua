project "TwoNet"
	kind "StaticLib"
	language "C++"

	targetdir ("lib")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tpch.h"
	pchsource "src/tpch.cpp" 

	files
	{
		"src/**.cpp",
		"include/TwoNet/**.h"
	}

	includedirs {
		"include/TwoNet"
	}

	defines { }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Debug"
		symbols "On"
	
