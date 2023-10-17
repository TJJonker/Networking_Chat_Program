#include "pch.h"
#include "Networking.h"
#include <TwoNet/Protocols/TwoProt.h>


Networking::Networking()
	:m_Client(nullptr) { }

Networking::~Networking() 
{ 
	Destroy();
}

bool Networking::Initialize(const char* ip, const char* port)
{
	m_Client = new Client(ip, port);
	return m_Client->Initialize();
}

void Networking::Destroy()
{
	delete m_Client;
}

bool Networking::Connect(std::string clientID)
{
	return m_Client->Connect(clientID);
}

bool Networking::RequestRooms(std::function<void(std::vector<std::string>)> callback)
{
	int result;
	TwoNet::Buffer buffer;
	std::string command = "LIST_ROOMS";

	TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length());
	result = m_Client->SendData(buffer);
	if (!result) 
		return false;

    std::thread([&, callback]()
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));

            int result;
            TwoNet::Buffer buffer; 

            result = m_Client->ReceiveData(buffer);
            if (result) {
                std::vector<std::string> roomNames;
                while (true) {
                    const char* data = TwoNet::TwoProt::DeserializeData(buffer);
                    if (data == nullptr)
                        break;
                    roomNames.push_back(data);
                }
                callback(roomNames);
            }
        }
    ).detach();

	TWONET_LOG_INFO("This log should come before the rooms 2.");
	return true;
}

