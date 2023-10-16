#include "pch.h"
#include "Commands.h"
#include <TwoNet/Protocols/TwoProt.h>

bool Commands::SendListOfRooms(SOCKET socket, NetworkServer& server, RoomManager& roomManager)
{
	int result;

	TwoNet::Buffer buffer;

	std::vector<std::string> roomNames = roomManager.GetRoomNames();
	for (std::string name : roomNames)
		TwoNet::TwoProt::SerializeData(buffer, name.c_str(), name.length());

	result = server.SendData(socket, buffer);
	if (!result) {
		TWONET_LOG_WARNING("Failed to send list of rooms.");
		return false;
	}

	return true;
}
