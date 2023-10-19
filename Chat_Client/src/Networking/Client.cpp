#include "pch.h"
#include "Client.h"
#include "TwoNet/Protocols/TwoProt.h"

#define TERMINATE(message) { TWONET_LOG_ERROR(message); Client::Terminate(); return false; }

Client::Client(const char* ip, const char* port)
	: m_IP(ip), m_Port(port), m_ClientSocket(INVALID_SOCKET), m_WsaData(), m_ServerInfo(nullptr) { }

Client::~Client() { }

bool Client::Initialize()
{
	int result;

	result = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
	if (result != 0)
		TERMINATE("WSAStartup failed.");

	// Configuring
	addrinfo hints; 
	ZeroMemory(&hints, sizeof(hints)); 
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_protocol = IPPROTO_TCP; 
	hints.ai_flags = AI_PASSIVE; 
	 
	m_ClientSocket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (m_ClientSocket == INVALID_SOCKET)
		TERMINATE("Error creating socket.");

	result = getaddrinfo(m_IP, m_Port, &hints, &m_ServerInfo);
	if (result != 0)
		TERMINATE("Retrieving server info failed.");

	return true;
}

void Client::Terminate()
{
	if (m_ClientSocket != INVALID_SOCKET)
		closesocket(m_ClientSocket);

	if (m_ServerInfo)
		freeaddrinfo(m_ServerInfo);

	WSACleanup();
}

bool Client::Connect(std::string clientID, std::string* connectionMessage)
{
	int result = connect(m_ClientSocket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen);
	if (result == SOCKET_ERROR)
		TERMINATE("Connection failed");

	TwoNet::Buffer buffer;
	TwoNet::TwoProt::SerializeData(buffer, clientID.c_str(), clientID.length());

	send(m_ClientSocket, buffer.GetBufferData(), buffer.GetSize(), 0);

	buffer.Clear();
	result = ReceiveData(buffer);
	const char* message = TwoNet::TwoProt::DeserializeData(buffer);
	if (connectionMessage) {
		std::string m(message);
		(*connectionMessage) = m;
	}

	return true;
}

void Client::SendData(TwoNet::Buffer& buffer, std::function<void(TwoNet::Buffer)> callback)
{
	Request* request = new Request();
	request->buffer = std::make_shared<TwoNet::Buffer>(buffer);
	request->callback = callback;

	m_Requests.push(request);
	HandleData();
}

bool Client::ReceiveData(TwoNet::Buffer& receivedDataBuffer)
{
	const unsigned int maxBufferSize = 1024;
	char buffer[maxBufferSize];
	int totalBytesRead = 0;

	int bytesRead = recv(m_ClientSocket, buffer, maxBufferSize, 0);

	if (bytesRead > 0) {
		while (true) {
			// If there is data to be read.
			receivedDataBuffer.WriteBuffer(buffer, bytesRead);
			totalBytesRead += bytesRead;

			// If all the data is read.
			if (bytesRead < maxBufferSize)
				break;
		}
	}
	else if (bytesRead == 0) {
		// Clean disconnection
		CloseConnection();
		return false;
	}
	else {
		// Error or disconnection
		return false;
	}

	return true;
}

bool Client::CloseConnection()
{
	if (m_ClientSocket != INVALID_SOCKET) {
		closesocket(m_ClientSocket);
		return true;
	}

	return false;
}

void Client::HandleData()
{
	if (m_IsHandlingRequest)
		return;

	if (m_Requests.size() <= 0)
		return;

	Request* newRequest = m_Requests.front();
	m_Requests.pop();

	int result = send(m_ClientSocket, newRequest->buffer->GetBufferData(), newRequest->buffer->GetSize(), 0);
	if (result == SOCKET_ERROR) {
		TWONET_LOG_WARNING("Error while sending data.");
		m_IsHandlingRequest = false;
	}
	
	std::function<void(TwoNet::Buffer)> callback = newRequest->callback;

	std::thread([&, callback]()
		{
			int result;
			TwoNet::Buffer buffer;

			result = ReceiveData(buffer);
			if (result) 
				callback(buffer);

			m_IsHandlingRequest = false;
		}
	).detach();
}
