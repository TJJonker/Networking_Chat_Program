#include "pch.h"

#include <WinSock2.h>
#include "Server/NetworkServer.h"

#include <TwoNet/Buffer/Buffer.h>
#include <TwoNet/Protocols/TwoProt.h>
#include <Server/Room.h>

//using CommandFunction = std::function<void>;

NetworkServer server("127.0.0.1", "8412");
//std::vector<Room> rooms;

//void SendListOfRooms(SOCKET socket) {
//	//TwoNet::Buffer buffer;
//	//TwoNet::TwoProt::SerializeData(buffer);
//	//server.sen
//}

int main() {
	TwoNet::Log::Init();

	//std::map<const char*, CommandFunction> commands;
	//commands.insert({ "LIST_ROOMS", });

	bool result = server.Initialize();
	

	while (true) {
		server.ListenForConnections();
	}
}