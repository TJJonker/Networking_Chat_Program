#pragma once
#include <Server/NetworkServer.h>
class Room
{
private:
	std::string m_Name;
	size_t m_MaxConnections;
	std::map<SOCKET, std::shared_ptr<Client>> m_ConnectedClients;

	std::vector<std::string> m_Messages;

public:
	Room(std::string name, size_t maxConnections = 10);

	std::string GetName() const { return m_Name; }
	bool IsSocketConnected(SOCKET socket) { return m_ConnectedClients.count(socket); }
	bool AddClient(std::shared_ptr<Client>);
	bool RemoveClient(std::shared_ptr<Client>);
	std::vector<std::string> GetMessages();

	void SendChatMessage(const std::shared_ptr<Client> client, std::string& message);
};

