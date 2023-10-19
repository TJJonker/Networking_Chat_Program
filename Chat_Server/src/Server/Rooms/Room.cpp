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

	m_ConnectedClients.insert({client->Socket, client});

	// Hardcoded welcome message
	std::string message = client->ClientID + " joined the room!";
	m_Messages.push_back(message);

	return true;
}

bool Room::RemoveClient(std::shared_ptr<Client> client)
{
	if (!m_ConnectedClients.count(client->Socket)) {
		TWONET_LOG_WARNING("Failed to remove {0} from room {1}. Client is not connected to this room.", client->ClientID, m_Name);
			return false;
	}

	// Hardcoded leave message
	std::string message = client->ClientID + " left the room.";
	m_Messages.push_back(message);

	m_ConnectedClients.erase(client->Socket);
	return true;
}

std::vector<std::string> Room::GetMessages()
{
	std::vector<std::string> messages;
	for (std::string message : m_Messages)
		messages.push_back(message);
	return messages;
}

void Room::SendChatMessage(const std::shared_ptr<Client> client, std::string& text)
{
	m_Messages.push_back(text);
}

