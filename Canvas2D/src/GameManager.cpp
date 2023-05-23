#include "GameManager.h"

GameManager::GameManager()
{
	EventManager::Instance()->AddListener<OnClockEvent>(ClockEventListener);
}

GameManager::~GameManager()
{

}

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}

	return instance;
}

float GameManager::deltaTime = 0;

void GameManager::ClockEventListener(BaseEvent* event)
{
	OnClockEvent* args = (OnClockEvent*)event;
	deltaTime = args->deltaTime;
}