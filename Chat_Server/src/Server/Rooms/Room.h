#pragma once
#include <Server/NetworkServer.h>
#include "Message.h"
class Room
{
private:
	std::string m_Name;
	size_t m_MaxConnections;
	std::map<SOCKET, std::shared_ptr<Client>> m_ConnectedClients;

	std::function<void(const std::shared_ptr<Client>, const Message* message)> m_OnMessageSent;
	std::function<void(const std::shared_ptr<Client>)> m_onClientJoined;

public:
	Room(std::string name, size_t maxConnections = 10);

	std::string GetName() const { return m_Name; }
	bool AddClient(std::shared_ptr<Client>);
	bool RemoveClient(std::shared_ptr<Client>);

	void SendChatMessage(const std::shared_ptr<Client> client, std::string& message);

	void SetCallback_OnMessageSent(std::function<void(const std::shared_ptr<Client>, const Message* message)> onMessageSent);
	void SetCallback_OnClientJoined(std::function<void(const std::shared_ptr<Client>)> onClientJoined);
};

