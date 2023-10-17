#pragma once

#include "Server/NetworkServer.h"
#include <Server/Rooms/RoomManager.h>

class Commands
{
public:
	static bool SendListOfRooms(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager);
	static bool AddClientToRooms(std::shared_ptr<Client> client, std::string roomName, NetworkServer& server, RoomManager& roomManager);
};

