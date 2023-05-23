#pragma once

#include "gl_canvas2d.h"
#include "EventManager.h"
#include <chrono>

class GameManager
{
private:
	static GameManager* instance;
	GameManager();
	~GameManager();

public:
	static GameManager* Instance();
	float deltaTime;
	float time;

};

