#include "pch.h"
#include "LobbyState.h"
#include <TwoNet/Utils/Utils.h>

LobbyState::LobbyState(StateManager* stateManager, Networking* networking)
	: m_Networking(networking), m_StateManager(stateManager), m_RoomNames() { }

LobbyState::~LobbyState() { }

void LobbyState::OnEnter()
{
	m_Networking->RequestRooms([&](std::vector<std::string> roomNames) {
			m_RoomNames = roomNames;
			LOG_WARNING("Which room do you want to join? (Repeat the room name)"); 
	
			for (std::string& name : m_RoomNames) 
				LOG_WARNING(name); 
	
			std::string roomChoice = ChooseRoom();
			m_Networking->RequestJoinRoom(roomChoice, [&](std::string response) 
				{ 
					if (response == TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::FAILED)) {
						TWONET_LOG_ERROR("Failed to join the room. Please restart the application.");
						return;
					}

					LOG_WARNING("Joined the room!");
					m_StateManager->ChangeState(StateManager::AppState::ROOM);
				}
			);
		}
	);
}

void LobbyState::OnExit()
{
}

std::string LobbyState::ChooseRoom()
{
	std::string name;
	std::getline(std::cin, name);

	if (!IsARoom(name)) {
		LOG_WARNING("That's not a valid room, try again.");
		return ChooseRoom();
	}

	return name;
}

bool LobbyState::IsARoom(std::string& name)
{
	return std::find(m_RoomNames.begin(), m_RoomNames.end(), name) != m_RoomNames.end();
}
