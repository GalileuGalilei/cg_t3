#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Scenary.h"
#include "Scenes.h"
#include <chrono>

class GameManager : public IUpdatable
{
private:
	std::list<Bullet*> bulletPool;
	std::list<Enemy*> enemyPool;
	std::list<PowerUp*> powerUpPool;
	Scenary* scenary = nullptr;
	GameOverScene* gameOverScene = nullptr;

	int score = 0;
	float timerToSpawnEnemy = 0.0;
	float timerToPowerUp = 8;
	bool isGameOver = false;
	bool deleteEverything = false;
	bool restart = false;
	


	void DeleteDestroyedBullets();
	void DeleteDestroyedEnemies();
	void DeleteDestroyedPowerUps();

	GameManager();
	~GameManager();

	static GameManager* instance;
	static void ClockEventListener(BaseEvent* event);

public:
	static GameManager* Instance();
	static float deltaTime;
	static double time;

	Player* player = nullptr;
	Bounds* screenBounds = nullptr;

	void OnUpdate(OnUpdateEvent* args) override;

	void AddBullet(Bullet* bullet);
	void AddEnemy(Enemy* enemy);
	void AddPowerUp(PowerUp* powerUp);
	void SetScreen(Vector2 screenSize);
	void SetScenary(Scenary* scenary);

	void GameOver();
	void Menu();
	void Start();
	void OnGameOver();
	void AddScore(int Score);
	Enemy* FindClosestEnemy(Vector2 position);
};


#endif // !GAME_MANAGER