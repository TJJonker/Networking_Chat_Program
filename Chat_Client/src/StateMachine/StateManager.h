#pragma once
#include "State.h"


class StateManager
{
public:
	enum class AppState {
		CONNECTING,
		LOBBY,
		ROOM
	};

private:
	AppState m_CurrentState = AppState::CONNECTING;
	std::map<AppState, State*> m_States;

public:
	StateManager();
	~StateManager();

	void Initialize(std::map<AppState, State*>& states, AppState startState = AppState::CONNECTING);

	void ChangeState(AppState newState);
};

