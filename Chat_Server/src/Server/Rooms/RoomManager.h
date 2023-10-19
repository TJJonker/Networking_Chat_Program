#pragma once
#include "Room.h"

class RoomManager
{
private:
	std::map<std::string, Room*> m_Rooms;

public:
	RoomManager();
	~RoomManager();

	bool AddRoom(std::string name = "", Room* room = nullptr);
	bool DeleteRoom(std::string name);

	std::vector<std::string> GetRoomNames();
	Room* GetRoom(std::string& name);
	Room* GetRoom(SOCKET socket);	
};

