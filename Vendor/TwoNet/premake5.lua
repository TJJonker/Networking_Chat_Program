project "TwoNet"
	kind "StaticLib"
	language "C++"

	targetdir ("lib")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tpch.h"
	pchsource "include/TwoNet/tpch.cpp" 

	files
	{
		"include/TwoNet/**.cpp",
		"include/TwoNet/**.h"
	}

	includedirs {
		"include"
	}

	defines { }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Debug"
		symbols "On"
	
