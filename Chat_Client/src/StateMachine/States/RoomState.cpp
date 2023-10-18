#include "pch.h"
#include "RoomState.h"

RoomState::RoomState(StateManager* stateManager, Networking* networking)
	: m_StateManager(stateManager), m_Networking(networking) { }

RoomState::~RoomState() { }

void RoomState::OnEnter()
{
}

void RoomState::OnExit()
{
}

void RoomState::OnUpdate()
{
}
