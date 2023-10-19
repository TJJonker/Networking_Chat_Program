#include "pch.h"
#include "RoomState.h"
#include <conio.h>
#include <iostream>
#include <TwoNet/Utils/Utils.h>

RoomState::RoomState(StateManager* stateManager, Networking* networking)
	: m_StateManager(stateManager), m_Networking(networking) { }

RoomState::~RoomState() { }

void RoomState::OnEnter() 
{
	system("cls");
	m_ChangeState = false;
	GetUserInput();
	RetrieveMessages();
}

void RoomState::OnExit()
{
	m_AmountOfMessages = 0;
	system("cls");
}


void RoomState::GetUserInput()
{
	std::thread([&]()
		{
			std::string input;
			while (true) {
				std::getline(std::cin, input);
				if (input.empty())
					continue;

				if (input == "E") {
					m_Networking->RequestLeaveRoom([&](std::string response)
						{
							if (response == TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::SUCCESS)) { 
								m_ChangeState = true;
							}
							else {
								TWONET_LOG_ERROR("Error while leaving the room. Please restart the application.");
							}
						}
					);
				} 
				else {
					m_Networking->RequestSendMessage(input, [&](std::string response) {
							if (response == TwoNet::Utils::ResponseToString(TwoNet::Utils::Response::SUCCESS)) {
								GetUserInput();
							}
							else {
								TWONET_LOG_ERROR("Error while sending the message. Please restart the application.");
							}
						}
					);					
				}
				break;
				
			}
		}
	).detach();
}

void RoomState::RetrieveMessages()
{
	std::thread([&]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		m_Networking->CheckIncomingMessages([&](std::vector<std::string> messages)
			{
				if (messages.size() >= m_AmountOfMessages) {
					for (int i = m_AmountOfMessages; i < messages.size(); i++) {
						m_AmountOfMessages++;
						LOG_WARNING(messages[i]);
					}
				}

				if(m_ChangeState)
					m_StateManager->ChangeState(StateManager::AppState::LOBBY);
				else 
					RetrieveMessages();
			}
		);
		}
	).detach();
}

