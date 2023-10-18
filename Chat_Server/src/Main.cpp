#include "pch.h"

#include <WinSock2.h>
#include "Server/NetworkServer.h"

#include <TwoNet/Buffer/Buffer.h>
#include <TwoNet/Protocols/TwoProt.h>
#include <TwoNet/Serialization/Serialization.h>
#include <Server/Rooms/Room.h>

#include "Server/Commands/Commands.h"
#include <Server/Rooms/RoomManager.h>


NetworkServer server("127.0.0.1", "8412");
RoomManager roomManager;

std::map<std::string, CommandFunction> commands;

bool SendListOfRooms(std::shared_ptr<Client> client, TwoNet::Buffer& buffer) {
	return Commands::SendListOfRooms(client, server, roomManager);
}

bool AddClientToRoom(std::shared_ptr<Client> client, TwoNet::Buffer& buffer) {
	const char* roomName = TwoNet::TwoProt::DeserializeData(buffer);
	return Commands::AddClientToRooms(client, roomName, server, roomManager);
}

//bool SendMessage(SOCKET socket, TwoNet::Buffer&) {
//
//}


void OnMessageSentCallback(const std::shared_ptr<Client> client, const Message* message) {
	TwoNet::Buffer buffer;
	TwoNet::TwoProt::SerializeData(buffer, message->Text.c_str(), message->Text.length());
	server.SendData(client->Socket, buffer);
}

void OnClientJoined(const std::shared_ptr<Client> client) {
	std::string welcomeMessage(client->ClientID + " Joined the room! Welcome!");
	TWONET_LOG_ERROR("Did it work?");
	TwoNet::Buffer buffer;
	TwoNet::TwoProt::SerializeData(buffer, welcomeMessage.c_str(), welcomeMessage.length());
	server.SendData(client->Socket, buffer);
}


int main() {

	TwoNet::Log::Init();

	commands.insert({ "LIST_ROOMS", SendListOfRooms });
	commands.insert({ "JOIN_ROOM", AddClientToRoom }); 

	std::string roomName1 = "R1";
	std::string roomName2 = "R2";
	std::string roomName3 = "R3";

	roomManager.AddRoom(roomName1);
	roomManager.AddRoom(roomName2);
	roomManager.AddRoom(roomName3);

	Room* room1 = roomManager.GetRoom(roomName1);
	Room* room2 = roomManager.GetRoom(roomName2);
	Room* room3 = roomManager.GetRoom(roomName3);

	room1->SetCallback_OnMessageSent(OnMessageSentCallback);
	room1->SetCallback_OnClientJoined(OnClientJoined);
	room2->SetCallback_OnMessageSent(OnMessageSentCallback);
	room2->SetCallback_OnClientJoined(OnClientJoined);
	room3->SetCallback_OnMessageSent(OnMessageSentCallback);
	room3->SetCallback_OnClientJoined(OnClientJoined);

	int result;
	result = server.Initialize();

	while (true) {
		server.ListenForConnections();
		server.ReceiveAndHandleData(commands);
	}
}

