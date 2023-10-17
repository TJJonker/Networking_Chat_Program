#include "pch.h"
#include "Room.h"

Room::Room(std::string name, size_t maxConnections)
	: m_Name(name), m_MaxConnections(maxConnections) { }

bool Room::AddClient(std::shared_ptr<Client> client)
{
	if (m_ConnectedClients.size() >= m_MaxConnections) {
		TWONET_LOG_WARNING("Failed to add '{0}' to room '{1}'. Room is full.", client->ClientID, m_Name);
		return false;
	}

	if (m_onClientJoined)
		m_onClientJoined(client, m_Messages);

	m_ConnectedClients.insert({client->Socket, client});
	return true;
}

bool Room::RemoveClient(std::shared_ptr<Client> client)
{
	if (!m_ConnectedClients.count(client->Socket)) {
		TWONET_LOG_WARNING("Failed to remove {0} from room {1}. Client is not connected to this room.", client->ClientID, m_Name);
			return false;
	}

	m_ConnectedClients.erase(client->Socket);
	return true;
}

void Room::SendChatMessage(const std::shared_ptr<Client> client, std::string& text)
{
	Message* message = new Message(client->ClientID, text);
	m_Messages.push_back(message);

	if(m_OnMessageSent)
		m_OnMessageSent(client, message);
}

void Room::SetCallback_OnMessageSent(std::function<void(const std::shared_ptr<Client>, const Message* message)> onMessageSent)
{
	m_OnMessageSent = onMessageSent;
}

void Room::SetCallback_OnClientJoined(std::function<void(const std::shared_ptr<Client>, const std::vector<Message*>& messageList)> onClientJoined)
{
	m_onClientJoined = onClientJoined;
}
