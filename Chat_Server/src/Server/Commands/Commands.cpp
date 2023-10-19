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

bool Commands::SendNewMessage(std::shared_ptr<Client> client, std::string message, NetworkServer& server, RoomManager& roomManager)
{
	TwoNet::Buffer buffer; 
	std::string response; 
	TWONET_LOG_TRACE("Check1");
	Room* room = roomManager.GetRoom(client->Socket);
	TWONET_LOG_TRACE(room->GetName());
	room->SendChatMessage(client, message);
	TWONET_LOG_TRACE("Check3");

	response = TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::SUCCESS); 
	TwoNet::TwoProt::SerializeData(buffer, response.c_str(), response.length()); 
	server.SendData(client->Socket, buffer); 

	return true;
}

bool Commands::LeaveRoom(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager)
{
	int result;
	TwoNet::Buffer buffer; 
	std::string response; 

	Room* room = roomManager.GetRoom(client->Socket);
	result = room->RemoveClient(client);
	if (!result) {
		response = TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::FAILED);
		TwoNet::TwoProt::SerializeData(buffer, response.c_str(), response.length()); 
		server.SendData(client->Socket, buffer); 
	}

	response = TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::SUCCESS); 
	TwoNet::TwoProt::SerializeData(buffer, response.c_str(), response.length()); 
	server.SendData(client->Socket, buffer); 

	return true;
}

bool Commands::GetMessages(std::shared_ptr<Client> client, NetworkServer& server, RoomManager& roomManager)
{
	int result;
	TwoNet::Buffer buffer;
	std::string response;

	Room* room = roomManager.GetRoom(client->Socket);
	if (!room) {
		response = TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::FAILED); 
		TwoNet::TwoProt::SerializeData(buffer, response.c_str(), response.length()); 
		server.SendData(client->Socket, buffer); 
		return false;
	}
	
	std::vector<std::string> messages = room->GetMessages();

	for (std::string message : messages) 
		TwoNet::TwoProt::SerializeData(buffer, message.c_str(), message.length());

	server.SendData(client->Socket, buffer);

	return true;
}
