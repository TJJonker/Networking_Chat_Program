workspace "Chat_Program"
	architecture "x64"
	startproject "Chat_Client"

	configurations {
		"Debug"
	}

solutionDir = "%{wks.location}/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "TwoNet"
include "Chat_Client"

includeDirs = {}
includeDirs["TwoNet"] = "TwoNet/include"

libraryDirs = {}
libraryDirs["TwoNet"] = "TwoNet/lib"


