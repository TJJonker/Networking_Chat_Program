#pragma once
#include "Room.h"

class RoomManager
{
private:
	std::map<std::string, Room> m_Rooms;

public:
	RoomManager();
	~RoomManager();

	bool AddRoom(std::string name = "");
	bool DeleteRoom(std::string name);

	std::vector<std::string> GetRoomNames();
};

