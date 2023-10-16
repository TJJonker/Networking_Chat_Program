#include "pch.h"
#include <Networking/Client.h>
#include <TwoNet/Protocols/TwoProt.h>
#include <Networking/Room.h>
#include <TwoNet/Serialization/Serialization.h>


int main() {
	TwoNet::Log::Init();
	
	Client client("127.0.0.1", "8412");
	client.Initialize();
	client.Connect();

	std::string command = "LIST_ROOMS"; 
	TwoNet::Buffer buffer; 
	TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length());
	client.SendData(buffer);

	buffer.Clear();
	client.ReceiveData(buffer);

	
	std::vector<std::string> roomNames; 
	while (true) {
		const char* data = TwoNet::TwoProt::DeserializeData(buffer);
		if (data == nullptr)
			break;
		roomNames.push_back(data);
	}
	
	for(std::string name : roomNames)
		TWONET_LOG_INFO("Join: {0}", name);
}