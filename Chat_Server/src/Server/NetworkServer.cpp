#include "pch.h"
#include "NetworkServer.h"
#include <TwoNet/Protocols/TwoProt.h>

#define TERMINATE(message) { TWONET_LOG_ERROR(message); NetworkServer::Terminate(); return false; }

NetworkServer::NetworkServer(const char* ip, const char* port)
	: m_IP(ip), m_Port(port), m_ListenSocket(INVALID_SOCKET), m_ServerInfo(nullptr), m_WsaData(), m_Readfds() { }

NetworkServer::~NetworkServer()
{
	Terminate();
}

bool NetworkServer::Initialize()
{
	int result;

	m_Timeout.tv_sec = 0; 
	m_Timeout.tv_usec = 0; 

	// Initializing
	result = WSAStartup(MAKEWORD(2, 2), &m_WsaData);
	if (result)
		TERMINATE("WSA startup failed.");

	// Configuring
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Retrieving
	result = getaddrinfo(m_IP, m_Port, &hints, &m_ServerInfo);
	if (result)
		TERMINATE("Retrieving server info failed.")

	// Creating
	m_ListenSocket = socket(m_ServerInfo->ai_family, m_ServerInfo->ai_socktype, m_ServerInfo->ai_protocol);
	if (m_ListenSocket == INVALID_SOCKET)
		TERMINATE("Socket Creation failed.");

	// Binding
	result = bind(m_ListenSocket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen);
	if (result == SOCKET_ERROR)
		TERMINATE("Socket Creation failed.");

	// Listening
	result = listen(m_ListenSocket, SOMAXCONN);
	if (result == SOCKET_ERROR)
		TERMINATE("Socket listening failed.");

	FD_ZERO(&m_Readfds);
	FD_SET(m_ListenSocket, &m_Readfds);

	return true;
}

void NetworkServer::ListenForConnections()
{
	fd_set temp = m_Readfds;
	int result;

	result = select(m_ListenSocket, &temp, NULL, NULL, &m_Timeout);
	if (result == SOCKET_ERROR) {
		TWONET_LOG_ERROR("Select error... (ERROR: {0})", WSAGetLastError());
		return;
	}

	if (FD_ISSET(m_ListenSocket, &temp)) {
		sockaddr_in remoteaddr;
		int addresslen = sizeof(remoteaddr);
		SOCKET newfd = accept(m_ListenSocket, (sockaddr*)&remoteaddr, &addresslen);

		if (newfd == INVALID_SOCKET) {
			TWONET_LOG_ERROR("Socket acceptance failed... (Error: {0})", WSAGetLastError());
			return;
		}
		
		FD_SET(newfd, &m_Readfds);
			
		TwoNet::Buffer buffer;
		if (ReceiveData(buffer, newfd)) {
				
			const void* data = TwoNet::TwoProt::DeserializeData(buffer);
			std::string clientID(static_cast<const char*>(data));
			static int ID = 1;
			clientID = clientID == " " ? std::to_string(ID++) : clientID;

			m_Clients.insert({ newfd, std::make_shared<Client>(newfd, clientID) });
			TWONET_LOG_TRACE("New ID: {0}", clientID);
		}

		buffer.Clear();
		std::string welcomeMessage = "Welcome to the Void!";
		TwoNet::TwoProt::SerializeData(buffer, welcomeMessage.c_str(), welcomeMessage.length());
		result = SendData(newfd, buffer);
		if (!result) {
			TWONET_LOG_WARNING("Failed to send handshake.");
			return;
		}

		TWONET_LOG_TRACE("Connection made.");		
	}
}

bool NetworkServer::SendData(SOCKET socket, TwoNet::Buffer& buffer)
{
	int result;

	result = send(socket, buffer.GetBufferData(), buffer.GetSize(), 0);
	if (result == SOCKET_ERROR) {
		TWONET_LOG_WARNING("Error while sending data.");
		return false;
	}

	return true;
}

bool NetworkServer::ReceiveData(TwoNet::Buffer& receivedDataBuffer, SOCKET clientSocket)
{
	const unsigned int maxBufferSize = 1024;
	char buffer[maxBufferSize];
	int totalBytesRead = 0;

	while (true) {
		int bytesRead = recv(clientSocket, buffer, maxBufferSize, 0);

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
			CloseConnection(clientSocket);
			return false;
		}
		else {
			// Error or disconnection
			return false;
		}
	}

	return true;
}

void NetworkServer::ReceiveAndHandleData(std::map<std::string, CommandFunction> commands)
{
	int result;
	fd_set temp = m_Readfds;

	std::map<SOCKET, std::shared_ptr<Client>>::iterator it;
	for (it = m_Clients.begin(); it != m_Clients.end(); it++) {
		SOCKET socket = it->first;
		result = select(socket, &temp, NULL, NULL, &m_Timeout);

		if (FD_ISSET(socket, &temp) && socket != m_ListenSocket) {

			// Data
			TwoNet::Buffer buffer;
			result = ReceiveData(buffer, socket);
			if (!result)
				continue;

			const char* data = TwoNet::TwoProt::DeserializeData(buffer);
			std::string command(data);

			// Check command
			if (!commands.count(command)) {
				TWONET_LOG_WARNING("Command could not be found: {0}", command);
				continue;
			}

			// Retrieve important data
			if (!m_Clients.count(socket)) {
				TWONET_LOG_WARNING("Failed retrieving client. No entry with given socket");
				continue;
			}

			// Run command
			result = commands[command](m_Clients[socket], buffer);
			if (!result) {
				TWONET_LOG_WARNING("Error while running command: {0}", command);
				continue;
			}

			FD_CLR(socket, &temp);
		}
	}
}

bool NetworkServer::CloseConnection(SOCKET clientSocket)
{
	if (clientSocket != INVALID_SOCKET) {
		closesocket(clientSocket);
		return true;
	}

	return false;
}

void NetworkServer::Terminate()
{
	if (m_ListenSocket != INVALID_SOCKET) 
		closesocket(m_ListenSocket);

	if (m_ServerInfo) 
		freeaddrinfo(m_ServerInfo);

	WSACleanup();
}


