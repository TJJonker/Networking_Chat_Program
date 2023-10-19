#pragma once
#include "StateMachine/State.h"
#include <Networking/Networking.h>
#include <StateMachine/StateManager.h>

class ConnectingState : public State
{
private:
	Networking* m_Networking;
	StateManager* m_StateManager;

public:
	ConnectingState(StateManager* stateManager, Networking* networking);
	~ConnectingState();

	void OnEnter() override;
	void OnExit() override;
};

