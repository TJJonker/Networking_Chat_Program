#include "pch.h"
#include "StateManager.h"
#include "States/ConnectingState.h"

StateManager::StateManager() { }

StateManager::~StateManager() { }

void StateManager::Initialize(std::map<AppState, State*>& states, AppState startState)
{
	m_States = states;
	ChangeState(startState);
}

void StateManager::ChangeState(AppState newState)
{
	m_States[m_CurrentState]->OnExit();
	m_CurrentState = newState;
	m_States[m_CurrentState]->OnEnter();
}
