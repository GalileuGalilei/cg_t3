#pragma once

#include "gl_canvas2d.h"
#include "GameEvents.h"
#include <chrono>

class GameManager
{
private:
	static GameManager* instance;
	GameManager();
	~GameManager();
	static void ClockEventListener(BaseEvent* event);

public:
	static GameManager* Instance();
	static float deltaTime;
};

