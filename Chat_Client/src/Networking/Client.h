#pragma once
#include <TwoNet/Buffer/Buffer.h>
#include "Request.h"

class Client
{
private:
	WSADATA m_WsaData;
	SOCKET m_ClientSocket;
	addrinfo* m_ServerInfo;

	const char* m_IP;
	const char* m_Port;

	std::queue<Request*> m_Requests;
	bool m_IsHandlingRequest = false;

public:
	Client(const char* ip, const char* port);
	~Client();

	bool Initialize();
	void Terminate();
	
	bool Connect(std::string clientID = "", std::string* connectionMessage = nullptr);
	void SendData(TwoNet::Buffer& buffer, std::function<void(TwoNet::Buffer)>);
	bool ReceiveData(TwoNet::Buffer& receivedDataBuffer);

	bool CloseConnection();

private:
	void HandleData();
};

