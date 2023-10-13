#pragma once
#include "pch.h"

class NetworkServer
{
private:
	SOCKET m_ListenSocket;
	addrinfo* m_ServerInfo;
	WSADATA m_WsaData;

	const char* m_IP;
	const char* m_Port;


public:
	NetworkServer(const char* ip, const char* port);
	~NetworkServer();

	void Initialize();
	void ListenForConnections();
	void SendData();
	void ReceiveData();
	void CloseConnection();
	void Terminate();
};

