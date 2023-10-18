#pragma once
#include "Client.h"

class Networking
{
private:
	Client* m_Client;

public:

	Networking();
	~Networking();

	bool Initialize(const char* ip, const char* port);
	void Destroy();

	bool Connect(std::string clientID = " ", std::string* welcomeMessage = nullptr);

	bool RequestRooms(std::function<void(std::vector<std::string>)> callback);
	bool RequestJoinRoom(std::string roomName, std::function<void(std::string)> callback);
};

