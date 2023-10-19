#pragma once

#include "Server/NetworkServer.h"
#include <Server/Rooms/RoomManager.h>

class Commands
{
public:
	static bool SendListOfRooms(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager);
	static bool AddClientToRooms(std::shared_ptr<Client> client, std::string roomName, NetworkServer& server, RoomManager& roomManager);
	static bool SendNewMessage(std::shared_ptr<Client> client, std::string message, NetworkServer& server, RoomManager& roomManager);
	static bool LeaveRoom(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager);
	static bool GetMessages(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager);
};

