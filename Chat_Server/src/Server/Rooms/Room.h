#pragma once
class Room
{
private:
	std::string m_Name;

public:
	Room(std::string name);

	std::string GetName() const { return m_Name; }
};

