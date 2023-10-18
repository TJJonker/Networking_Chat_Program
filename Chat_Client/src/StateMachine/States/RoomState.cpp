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
	system("cls");
}

void RoomState::OnUpdate()
{
	static auto start = std::chrono::high_resolution_clock::now();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

	if (duration.count() >= 2) {
		start = std::chrono::high_resolution_clock::now();
		TWONET_LOG_ERROR("Working on it!");
		m_Networking->CheckIncomingMessages([](std::string message)
			{
				LOG_INFO(message);
			}
		);
	}
}
