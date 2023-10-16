#pragma once
#include <Server/NetworkServer.h>
class Room
{
private:
	std::string m_Name;
	size_t m_MaxConnections;
	std::map<std::string, Client*> m_ConnectedClients;

	std::vector<std::string> m_Messages;

	std::function<void(const Client&, const std::string& message)> m_onMessageSent;
	std::function<void(const Client&, const std::string& message)> m_onClientJoined;

public:
	Room(std::string name, size_t maxConnections = 10);

	std::string GetName() const { return m_Name; }
	bool AddClient(Client& client);
	bool RemoveClient(Client& client);

	// OnMessageSent(Client client, std::string message) callback

};

