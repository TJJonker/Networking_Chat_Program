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
	TwoNet::Buffer buffer;
	std::string command = "LIST_ROOMS";

	TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length());
    m_Client->SendData(buffer, [&, callback](TwoNet::Buffer buffer) {
            std::vector<std::string> roomNames;
            while (true) {
                const char* data = TwoNet::TwoProt::DeserializeData(buffer);
                if (data == nullptr)
                    break;
                roomNames.push_back(data);
            }
            callback(roomNames);
        });

	return true;
}

bool Networking::RequestJoinRoom(std::string roomName, std::function<void(std::string)> callback)
{
    TwoNet::Buffer buffer;
    std::string command = "JOIN_ROOM";
    TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length()); 
    TwoNet::TwoProt::SerializeData(buffer, roomName.c_str(), roomName.length());

    m_Client->SendData(buffer, [&, callback](TwoNet::Buffer buffer) {
            const char* data = TwoNet::TwoProt::DeserializeData(buffer);
            if (data)
                callback(data);
        }
    );

    return true;
}

bool Networking::RequestLeaveRoom(std::function<void(std::string)> callback)
{
    TwoNet::Buffer buffer; 
    std::string command = "LEAVE_ROOM"; 

    TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length());
    m_Client->SendData(buffer, [&, callback](TwoNet::Buffer buffer) {
            const char* data = TwoNet::TwoProt::DeserializeData(buffer);
            if (data)
                callback(data);
        }
    );

    return true;
}

bool Networking::RequestSendMessage(std::string message, std::function<void(std::string)> callback)
{
    TwoNet::Buffer buffer;
    std::string command = "SEND_MESSAGE";

    TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length()); 
    TwoNet::TwoProt::SerializeData(buffer, message.c_str(), message.length());

    m_Client->SendData(buffer, [&, callback](TwoNet::Buffer buffer) {
            const char* data = TwoNet::TwoProt::DeserializeData(buffer);
            if (data)
                callback(data);
        }
    );

    return true;
}

bool Networking::CheckIncomingMessages(std::function<void(std::vector<std::string>)> callback)
{
    TwoNet::Buffer buffer; 
    std::string command = "GET_MESSAGES";

    TwoNet::TwoProt::SerializeData(buffer, command.c_str(), command.length());
    m_Client->SendData(buffer, [&, callback](TwoNet::Buffer buffer) {
            std::vector<std::string> newMessages;
            while (true) {
                const char* data = TwoNet::TwoProt::DeserializeData(buffer);
                if (data == nullptr)
                    break;
                newMessages.push_back(data);
            }
            callback(newMessages);
        }
    );

    return true;
}

