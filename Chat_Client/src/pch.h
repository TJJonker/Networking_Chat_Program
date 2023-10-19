#pragma once

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#include "Debug/Assertion.h"
#include "Debug/Log.h"

#include <future>
#include <map>
#include <queue>