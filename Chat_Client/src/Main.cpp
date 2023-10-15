#include "pch.h"
#include <Networking/Client.h>
#include <TwoNet/Protocols/TwoProt.h>
#include <Networking/Room.h>


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
	const void* data = TwoNet::TwoProt::DeserializeData(buffer);
	const char* roomNames(static_cast<const char*>(data));
	TWONET_LOG_INFO(roomNames);
}