#include "pch.h"

#include <WinSock2.h>
#include "Server/NetworkServer.h"

#include <TwoNet/Buffer/Buffer.h>
#include <TwoNet/Protocols/TwoProt.h>
#include <Server/Room.h>

NetworkServer server("127.0.0.1", "8412");
std::vector<Room> rooms;
std::map<std::string, CommandFunction> commands;

bool SendListOfRooms(SOCKET socket) {
	int result;

	std::vector<std::string> roomNames;
	for (Room room : rooms)
		roomNames.push_back(room.GetName());

	TwoNet::Buffer buffer;
	TwoNet::TwoProt::SerializeData(buffer, roomNames.data(), roomNames.size());
	result = server.SendData(socket, buffer);
	if (!result) {
		TWONET_LOG_WARNING("Failed to send list of rooms.");
		return false;
	}

	return true;
}

int main() {
	TwoNet::Log::Init();

	commands.insert({ "LIST_ROOMS", SendListOfRooms });
	commands["LIST_ROOMS"] = SendListOfRooms;

	Room room1("Room 1");
	Room room2("Room 2");
	rooms.push_back(room1);
	rooms.push_back(room2);

	bool result = server.Initialize();	

	while (true) {
		server.ListenForConnections();
		server.ReceiveAndHandleData(commands);
	}
}