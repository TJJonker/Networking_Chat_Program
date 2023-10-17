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

	bool Connect(std::string clientID = " ");

	bool RequestRooms(std::function<void(std::vector<std::string>)>);
};

