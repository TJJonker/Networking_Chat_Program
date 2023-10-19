#include "pch.h"
#include <Networking/Networking.h>
#include <StateMachine/StateManager.h>
#include "StateMachine/States/ConnectingState.h"
#include "StateMachine/States/LobbyState.h"
#include "StateMachine/States/RoomState.h"
#include <TwoNet/Protocols/TwoProt.h>


int main() {
	TwoNet::Log::Init();

	Networking* networking = new Networking();
	networking->Initialize("127.0.0.1", "8412");  
	StateManager* stateManager = new StateManager();   
	
	std::map<StateManager::AppState, State*> states;

	states.insert({ StateManager::AppState::CONNECTING, new ConnectingState(stateManager, networking)});
	states.insert({ StateManager::AppState::LOBBY, new LobbyState(stateManager, networking)});
	states.insert({ StateManager::AppState::ROOM, new RoomState(stateManager, networking)});
	stateManager->Initialize(states);

	while (true);
}