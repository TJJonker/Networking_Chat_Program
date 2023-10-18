#pragma once
#include "StateMachine/State.h"
#include "StateMachine/StateManager.h"
#include "Networking/Networking.h"


class RoomState : public State
{
private:
	Networking* m_Networking;
	StateManager* m_StateManager;

public:
	RoomState(StateManager* stateManager, Networking* networking);
	~RoomState();

	void OnEnter() override;
	void OnExit() override;
	void OnUpdate() override;
};

