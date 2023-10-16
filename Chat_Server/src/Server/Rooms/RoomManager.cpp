#include "pch.h"
#include "RoomManager.h"

RoomManager::RoomManager() { }

RoomManager::~RoomManager() { }

bool RoomManager::AddRoom(std::string name)
{
	static unsigned int roomID = 1;
	name = name == "" ? "Room " + roomID++ : name;

	if (m_Rooms.count(name)) {
		TWONET_LOG_WARNING("Failed to add room. Room name '{0}' already exists.", name);
		return false;
	}

	m_Rooms.insert({ name, Room(name) });

	return true;
}

bool RoomManager::DeleteRoom(std::string name)
{
	if (!m_Rooms.count(name)) {
		TWONET_LOG_WARNING("Failed to delete room. Room with name '{0}' does not exists.", name);
		return false;
	}

	m_Rooms.erase(name);
	return true;
}

std::vector<std::string> RoomManager::GetRoomNames()
{
	std::vector<std::string> roomNames;
	std::map<std::string, Room>::iterator it;

	for (it = m_Rooms.begin(); it != m_Rooms.end(); it++)
		roomNames.push_back(it->second.GetName());

	return roomNames;
}
