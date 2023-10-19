#pragma once
#include "StateMachine/State.h"
#include <Networking/Networking.h>
#include <StateMachine/StateManager.h>

class LobbyState : public State
{
private:
	Networking* m_Networking;
	StateManager* m_StateManager;

	std::vector<std::string> m_RoomNames;

	std::string ChooseRoom();
	bool IsARoom(std::string&);

public:
	LobbyState(StateManager* stateManager, Networking* networking);
	~LobbyState();

	void OnEnter() override;
	void OnExit() override;
};

