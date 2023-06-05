#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}

	return instance;
}

GameManager::GameManager()
{
	srand(time(NULL));
	EventManager::Instance()->AddListener<OnClockEvent>(ClockEventListener);
	EventManager::Instance()->AddListener<OnRenderEvent>(IRenderable::RenderAll);
	EventManager::Instance()->AddListener<OnClickEvent>(IClickable::ClickAll);
	EventManager::Instance()->AddListener<OnMouseOverEvent>(IClickable::MouseOverAll);
	EventManager::Instance()->AddListener<OnKeyEvent>(IKeyable::KeyAll);
}

GameManager::~GameManager()
{
	EventManager::Instance()->RemoveListener<OnClockEvent>(ClockEventListener);
	EventManager::Instance()->RemoveListener<OnRenderEvent>(IRenderable::RenderAll);
	EventManager::Instance()->RemoveListener<OnClickEvent>(IClickable::ClickAll);
	EventManager::Instance()->RemoveListener<OnMouseOverEvent>(IClickable::MouseOverAll);
	EventManager::Instance()->RemoveListener<OnKeyEvent>(IKeyable::KeyAll);
}

float GameManager::deltaTime = 0;

void GameManager::ClockEventListener(BaseEvent* event)
{
	OnClockEvent* args = (OnClockEvent*)event;
	deltaTime = args->deltaTime;
}