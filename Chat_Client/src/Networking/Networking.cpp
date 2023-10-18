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

bool Networking::Connect(std::string clientID, std::string* welcomeMessage)
{
	return m_Client->Connect(clientID, welcomeMessage);
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

    buffer.Clear();

    result = m_Client->ReceiveData(buffer);
    if (!result)
        return false;

    std::vector<std::string> roomNames;
    while (true) {
        const char* data = TwoNet::TwoProt::DeserializeData(buffer);
        if (data == nullptr)
            break;
        roomNames.push_back(data);
    }
    callback(roomNames);
 
	return true;
}

bool Networking::RequestJoinRoom(std::string roomName, std::function<void(std::string)> callback)
{
    int result;
    TwoNet::Buffer buffer;
    std::string command = "JOIN_ROOM";
    TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length()); 
    TwoNet::TwoProt::SerializeData(buffer, roomName.c_str(), roomName.length());

    result = m_Client->SendData(buffer); 
    if (!result)
        return false;

    std::thread([&, callback]()
        {
            int result;
            TwoNet::Buffer buffer;

            result = m_Client->ReceiveData(buffer);
            if (result) {
                const char* data = TwoNet::TwoProt::DeserializeData(buffer);
                if (data)
                    callback(data);
            }
        }
    ).detach();
    
    return true;
}

bool Networking::CheckIncomingMessages(std::function<void(std::string)> callback)
{
    std::thread([&, callback]()
        {
            int result;
            TwoNet::Buffer buffer;

            result = m_Client->ReceiveData(buffer);
            if (result) {
                const char* data = TwoNet::TwoProt::DeserializeData(buffer);
                callback(data);
            }
        }
    ).detach();
    return true;
}

