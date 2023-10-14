workspace "Chat_Program"
	architecture "x64"
	startproject "Chat_Client" 

	configurations {
		"Debug"
	}

solutionDir = "%{wks.location}/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Vendor/TwoNet"
include "Chat_Server"
include "Chat_Client"

includeDirs = {}
includeDirs["TwoNet"] = "Vendor/TwoNet/include"
includeDirs["SPDLOG"] = "Vendor/spdlog/include"

libraryDirs = {}
libraryDirs["TwoNet"] = "Vendor/TwoNet/lib"


