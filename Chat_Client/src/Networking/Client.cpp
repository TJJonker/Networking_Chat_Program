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

bool Client::Connect()
{
	TWONET_LOG_TRACE("Trying to connect to the server...");
	int result = connect(m_ClientSocket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen);
	if (result == SOCKET_ERROR)
		TERMINATE("Connection failed");

	TwoNet::Buffer buffer;
	std::string clientID = "Tom Jonker";
	TwoNet::TwoProt::SerializeData(buffer, clientID.c_str(), clientID.length());

	result = SendData(buffer);
	if (result == 0) {
		TWONET_LOG_WARNING("Failed to send initial data.");
		return false;
	}

	buffer.Clear();
	result = ReceiveData(buffer);
	const void* data = TwoNet::TwoProt::DeserializeData(buffer);
	std::string message(static_cast<const char*>(data));
	TWONET_LOG_TRACE(message);

	return true;
}

bool Client::SendData(TwoNet::Buffer& buffer)
{
	int result = send(m_ClientSocket, buffer.GetBufferData(), buffer.GetSize(), 0);
	if (result == SOCKET_ERROR) {
		TWONET_LOG_WARNING("Error while sending data.");
		return false;
	}

	return true;
}

bool Client::ReceiveData(TwoNet::Buffer& receivedDataBuffer)
{
	const unsigned int maxBufferSize = 1024;
	char buffer[maxBufferSize];
	int totalBytesRead = 0;

	while (true) {
		int bytesRead = recv(m_ClientSocket, buffer, maxBufferSize, 0);

		if (bytesRead > 0) {
			// If there is data to be read.
			receivedDataBuffer.WriteBuffer(buffer, bytesRead);
			totalBytesRead += bytesRead;

			// If all the data is read.
			if (bytesRead < maxBufferSize)
				break;
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
