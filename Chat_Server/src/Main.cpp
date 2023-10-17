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


int main() {

	TwoNet::Log::Init();

	commands.insert({ "LIST_ROOMS", SendListOfRooms});
	commands.insert({ "JOIN_ROOM", AddClientToRoom }); 

	roomManager.AddRoom("Chillinging Room 1");
	roomManager.AddRoom("Crazy Room 2");
	roomManager.AddRoom("Seducing Room 3");

	int result;
	result = server.Initialize();

	while (true) {
		server.ListenForConnections();
		server.ReceiveAndHandleData(commands);
	}
}

