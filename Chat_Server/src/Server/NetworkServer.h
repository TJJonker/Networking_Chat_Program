#pragma once
#include <TwoNet/Buffer/Buffer.h>


struct Client {
	SOCKET Socket;
	std::string ClientID;
};

class NetworkServer
{
private:
	SOCKET m_ListenSocket;
	addrinfo* m_ServerInfo;
	WSADATA m_WsaData;
	fd_set m_readfds;

	const char* m_IP;
	const char* m_Port;

	std::map<std::string, Client> m_Clients;

public:
	NetworkServer(const char* ip, const char* port);
	~NetworkServer();

	bool Initialize();
	void ListenForConnections();
	bool SendData(SOCKET socket, TwoNet::Buffer& buffer);
	bool ReceiveData(TwoNet::Buffer& receivedDataBuffer, SOCKET clientSocket);
	bool CloseConnection(SOCKET clientSocket);
	void Terminate();
};

