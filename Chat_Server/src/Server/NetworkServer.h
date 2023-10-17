#pragma once
#include <TwoNet/Buffer/Buffer.h>



struct Client {
	Client(SOCKET socket, std::string clientID) 
		: Socket(socket), ClientID(clientID) {}

	SOCKET Socket;
	std::string ClientID;
};

using CommandFunction = std::function<bool(std::shared_ptr<Client>, TwoNet::Buffer& buffer)>;

class NetworkServer
{
private:
	SOCKET m_ListenSocket;
	addrinfo* m_ServerInfo;
	WSADATA m_WsaData;
	fd_set m_Readfds;

	const char* m_IP;
	const char* m_Port;

	struct timeval m_Timeout;

	std::map<SOCKET, std::shared_ptr<Client>> m_Clients;

public:
	NetworkServer(const char* ip, const char* port);
	~NetworkServer();

	bool Initialize();
	void ListenForConnections();
	bool SendData(SOCKET socket, TwoNet::Buffer& buffer);
	bool ReceiveData(TwoNet::Buffer& receivedDataBuffer, SOCKET clientSocket);
	void ReceiveAndHandleData(std::map<std::string, CommandFunction> commands);
	bool CloseConnection(SOCKET clientSocket);
	void Terminate();
};

