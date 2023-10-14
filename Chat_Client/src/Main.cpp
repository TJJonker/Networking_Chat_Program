#include "pch.h"
#include <Networking/Client.h>


int main() {
	TwoNet::Log::Init();

	Client client("127.0.0.1", "8412");
	client.Initialize();
	client.Connect();
}