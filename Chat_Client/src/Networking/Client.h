#pragma once
#include <TwoNet/Buffer/Buffer.h>


class Client
{
private:
	WSADATA m_WsaData;
	SOCKET m_ClientSocket;
	addrinfo* m_ServerInfo;

	const char* m_IP;
	const char* m_Port;

public:
	Client(const char* ip, const char* port);
	~Client();

	bool Initialize();
	void Terminate();
	
	bool Connect(std::string clientID = "");
	bool SendData(TwoNet::Buffer& buffer);
	bool ReceiveData(TwoNet::Buffer& receivedDataBuffer);

	bool CloseConnection();
};

