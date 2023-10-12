project "Chat_Client"
	kind "ConsoleApp"
	language "C++"

	targetdir (solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp" 

	files
	{
		"src/**.cpp",
		"src/**.h"
	}

	includedirs {
		"src",
		solutionDir .. "%{includeDirs.TwoNet}"
	}

	libdirs {
		solutionDir .. "${libraryDirs.TwoNet}"
	}

	links {
		"TwoNet"
	}

	defines { }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Debug"
		symbols "On"
	
