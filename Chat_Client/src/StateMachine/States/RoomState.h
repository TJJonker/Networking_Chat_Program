#pragma once
#include "StateMachine/State.h"
#include "StateMachine/StateManager.h"
#include "Networking/Networking.h"


class RoomState : public State
{
private:
	Networking* m_Networking;
	StateManager* m_StateManager;

	int m_AmountOfMessages = 0;

	bool m_ChangeState = false;

	void GetUserInput();
	void RetrieveMessages();

public:
	RoomState(StateManager* stateManager, Networking* networking);
	~RoomState();

	void OnEnter() override;
	void OnExit() override;
};

