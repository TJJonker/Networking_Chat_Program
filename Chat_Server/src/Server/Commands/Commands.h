#pragma once

#include "Server/NetworkServer.h"
#include <Server/Rooms/RoomManager.h>

class Commands
{
public:
	static bool SendListOfRooms(SOCKET socket, NetworkServer& server, RoomManager& roomManager);
	static bool AddClientToRooms(SOCKET socket, NetworkServer& server, RoomManager& roomManager);
};

