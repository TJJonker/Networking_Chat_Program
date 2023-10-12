workspace "Chat_Program"
	architecture "x64"
	startproject "Chat_Client"

	configurations {
		"Debug"
	}

solutionDir = "%{wks.location}/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Chat_Client"
include "TwoNet"

includeDirs = {}
includeDirs["TwoNet"] = "TwoNet/include"

libraryDirs = {}
libraryDirs["TwoNet"] = "TwoNet/lib"


