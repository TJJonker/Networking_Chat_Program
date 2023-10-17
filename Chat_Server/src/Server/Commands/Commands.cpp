#include "pch.h"
#include "Commands.h"
#include <TwoNet/Protocols/TwoProt.h>
#include <TwoNet/Utils/Utils.h>

bool Commands::SendListOfRooms(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager)
{
	int result;

	TwoNet::Buffer buffer;

	std::vector<std::string> roomNames = roomManager.GetRoomNames();
	for (std::string name : roomNames)
		TwoNet::TwoProt::SerializeData(buffer, name.c_str(), name.length());

	result = server.SendData(client->Socket, buffer);
	if (!result) {
		TWONET_LOG_WARNING("Failed to send list of rooms.");
		return false;
	}

	return true;
}

bool Commands::AddClientToRooms(std::shared_ptr<Client> client, std::string roomName, NetworkServer& server, RoomManager& roomManager)
{
	int result;
	TwoNet::Buffer buffer;
	std::string response;

	Room* room = roomManager.GetRoom(roomName);
	result = room->AddClient(client);
	if (!result) {
		response = TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::FAILED);
		buffer.SerializeData(response.c_str(), response.length());
		server.SendData(client->Socket, buffer);
		return false;
	}

	response = TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::SUCCESS);
	TwoNet::TwoProt::SerializeData(buffer, response.c_str(), response.length());
	server.SendData(client->Socket, buffer);
	return true;
}
