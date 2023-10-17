#include "pch.h"
#include <Networking/Networking.h>


void WriteRoomList(std::vector<std::string> list) {
	for (const std::string& name : list)
		std::cout << name << std::endl;
}

int main() {
	TwoNet::Log::Init();
	Networking networking;
	networking.Initialize("127.0.0.1", "8412");
	networking.Connect();

	networking.RequestRooms(WriteRoomList);
	TWONET_LOG_INFO("This log should come before the rooms.");


}