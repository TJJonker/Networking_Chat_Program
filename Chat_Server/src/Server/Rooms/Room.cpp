#include "pch.h"
#include "Room.h"

Room::Room(std::string name, size_t maxConnections)
	: m_Name(name), m_MaxConnections(maxConnections) { }

bool Room::AddClient(Client& client)
{
	if (m_ConnectedClients.size() >= m_MaxConnections) {
		TWONET_LOG_WARNING("Failed to add '{0}' to room '{1}'. Room is full.", client.ClientID, m_Name);
		return false;
	}

	m_ConnectedClients.insert({ client.ClientID, &client });
	return true;
}

bool Room::RemoveClient(Client& client)
{
	if (!m_ConnectedClients.count(client.ClientID)) {
		TWONET_LOG_WARNING("Failed to remove {0} from room {1}. Client is not connected to this room.", client.ClientID, m_Name);
			return false;
	}

	m_ConnectedClients.erase(client.ClientID);
	return true;
}
