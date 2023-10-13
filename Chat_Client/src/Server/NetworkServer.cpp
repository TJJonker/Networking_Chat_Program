#include "pch.h"
#include "NetworkServer.h"

NetworkServer::NetworkServer(const char* ip, const char* port)
	: m_IP(ip), m_Port(port), m_ListenSocket(INVALID_SOCKET), m_ServerInfo(nullptr), m_WsaData() { }

NetworkServer::~NetworkServer()
{
	Terminate();
}

void NetworkServer::Initialize()
{

}

void NetworkServer::Terminate()
{
}


