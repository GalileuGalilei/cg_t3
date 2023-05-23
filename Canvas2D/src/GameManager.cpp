#include "GameManager.h"

GameManager::GameManager()
{
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

void GameManager::Update()
{
	auto start = std::chrono::high_resolution_clock::now();
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	deltaTime = elapsed.count();
	time += deltaTime;
}