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

bool SendNewMessage(std::shared_ptr<Client> client, TwoNet::Buffer& buffer) {
	const char* message = TwoNet::TwoProt::DeserializeData(buffer);
	return Commands::SendNewMessage(client, message, server, roomManager);
}

bool LeaveRoom(std::shared_ptr<Client> client, TwoNet::Buffer& buffer) {
	return Commands::LeaveRoom(client, server, roomManager);
}

bool GetMessages(std::shared_ptr<Client> client, TwoNet::Buffer& buffer) {
	return Commands::GetMessages(client, server, roomManager);
}


int main() {

	TwoNet::Log::Init();

	commands.insert({ "LIST_ROOMS", SendListOfRooms });
	commands.insert({ "JOIN_ROOM", AddClientToRoom }); 
	commands.insert({ "LEAVE_ROOM", LeaveRoom }); 
	commands.insert({ "SEND_MESSAGE", SendNewMessage }); 
	commands.insert({ "GET_MESSAGES", GetMessages }); 

	roomManager.AddRoom("R1");
	roomManager.AddRoom("R2");
	roomManager.AddRoom("R3");

	int result;
	result = server.Initialize();

	while (true) {
		server.ListenForConnections();
		server.ReceiveAndHandleData(commands);
	}
}

