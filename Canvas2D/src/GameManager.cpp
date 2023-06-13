#include "GameManager.h"
#include <chrono>

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
	srand(std::time(NULL));
	player = new Player();

	EventManager::Instance()->AddListener<OnUpdateEvent>(ClockEventListener);
	EventManager::Instance()->AddListener<OnUpdateEvent>(IUpdatable::UpdateAll);
	EventManager::Instance()->AddListener<OnRenderEvent>(IRenderable::RenderAll);
	EventManager::Instance()->AddListener<OnClickEvent>(IClickable::ClickAll);
	EventManager::Instance()->AddListener<OnMouseOverEvent>(IClickable::MouseOverAll);
	EventManager::Instance()->AddListener<OnKeyEvent>(IKeyable::KeyAll);
	EventManager::Instance()->AddListener<OnCollisionEvent>(ICollidable::TestColissionAll);
}

GameManager::~GameManager()
{
	EventManager::Instance()->RemoveListener<OnUpdateEvent>(ClockEventListener);
	EventManager::Instance()->RemoveListener<OnUpdateEvent>(IUpdatable::UpdateAll);
	EventManager::Instance()->RemoveListener<OnRenderEvent>(IRenderable::RenderAll);
	EventManager::Instance()->RemoveListener<OnClickEvent>(IClickable::ClickAll);
	EventManager::Instance()->RemoveListener<OnMouseOverEvent>(IClickable::MouseOverAll);
	EventManager::Instance()->RemoveListener<OnKeyEvent>(IKeyable::KeyAll);
}

float GameManager::deltaTime = 0;
double GameManager::time = 0;

void GameManager::ClockEventListener(BaseEvent* event)
{
	OnUpdateEvent* args = (OnUpdateEvent*)event;
	deltaTime = args->deltaTime;
	time += deltaTime;

	GameManager::Instance()->DeleteDestroyedBullets();
	GameManager::Instance()->DeleteDestroyedEnemies();
	GameManager::Instance()->DeleteDestroyedPowerUps();

	if (GameManager::instance->deleteEverything)
	{
		GameManager::instance->deleteEverything = false;
		delete GameManager::Instance()->player;
		delete GameManager::Instance()->scenary;
		GameManager::Instance()->player = nullptr;
		GameManager::Instance()->scenary = nullptr;
	}
}

void GameManager::OnUpdate(OnUpdateEvent* args)
{
	if (isGameOver)
	{
		OnGameOver();
	}

	if (restart)
	{
		restart = false;
		isGameOver = false;
		delete gameOverScene;
		gameOverScene = nullptr;

		player = new Player();
		SetScreen(screenBounds->size);
	}

	if (isGameOver) //cenário e inimigos 
	{
		return;
	}

	timerToSpawnEnemy += args->deltaTime;

	if (timerToSpawnEnemy > 2)
	{
		timerToSpawnEnemy = 0;
		scenary->SpawnEnemy(player);
	}

	timerToPowerUp += args->deltaTime;

	if (timerToPowerUp > 6)
	{
		timerToPowerUp = 0;
		scenary->SpawnPowerUp();
	}

	CV::color(0.7, 0.3, 0.7);
	std::string scoreText = "Score: " + std::to_string(score);
	CV::text(10, 70, scoreText.c_str());
}

void GameManager::DeleteDestroyedPowerUps()
{
	float dist = 0;
	for (PowerUp* powerUp : powerUpPool)
	{
		if (!screenBounds->RayCast(powerUp->GetPosition(), powerUp->GetDirection(), dist))
		{
			powerUp->Destroy();
		}

		if (powerUp->IsDestroyed())
		{
			powerUpPool.remove(powerUp);
			delete powerUp;
			break;
		}
	}
}

void GameManager::DeleteDestroyedBullets()
{
	for (Bullet* bullet : bulletPool)
	{
		if (!screenBounds->Contains(bullet->GetPosition()))
		{
			bullet->Destroy();
		}

		if (bullet->IsDestroyed())
		{
			bulletPool.remove(bullet);
			delete bullet;
			break;
		}
	}
}

void GameManager::DeleteDestroyedEnemies()
{
	for (Enemy* enemy : enemyPool)
	{
		if (enemy->IsDestroyed())
		{
			enemyPool.remove(enemy);
			delete enemy;
			break;
		}
	}
}

void GameManager::AddBullet(Bullet* bullet)
{
	bulletPool.push_back(bullet);
}

void GameManager::AddEnemy(Enemy* enemy)
{
	enemyPool.push_back(enemy);
}

void GameManager::AddPowerUp(PowerUp* powerUp)
{
	powerUpPool.push_back(powerUp);
}

void GameManager::SetScreen(Vector2 screenSize)
{
	if (screenBounds != nullptr)
		delete(screenBounds);
	this->screenBounds = new Bounds(Vector2(0, 0), screenSize);
	int screenWidth = screenSize.x;
	int screenHeight = screenSize.y;
	int border = 140;
	int range = 120;

	if (scenary == nullptr)
	{
		Scenary* scenary = new Scenary(screenSize, range, border);
		SetScenary(scenary);
	}
}

void GameManager::SetScenary(Scenary* scenary)
{
	if (this->scenary != nullptr)
	{
		delete(this->scenary);
	}

	this->scenary = scenary;
}

void GameManager::AddScore(int score)
{
	this->score += score;
}

Enemy* GameManager::FindClosestEnemy(Vector2 position)
{
	Enemy* closestEnemy = nullptr;

	for (Enemy* e : enemyPool)
	{
		if (closestEnemy == nullptr)
		{
			closestEnemy = e;
			continue;
		}
		if (Vector2::distance(position, e->GetPosition()) < Vector2::distance(position, closestEnemy->GetPosition()))
		{
			closestEnemy = e;
		}
	}

	return closestEnemy;
}

void GameManager::GameOver()
{
	isGameOver = true;
}

void GameManager::OnGameOver()
{
	if (gameOverScene != nullptr)
	{
		return;
	}

	for (Bullet* b : bulletPool)
	{
		b->Destroy();
	}

	for (Enemy* e : enemyPool)
	{
		e->Destroy();
	}

	gameOverScene = new GameOverScene([&]() { Start();}, score);
	deleteEverything = true;
}

void GameManager::Menu()
{

}

void GameManager::Start()
{
	if (gameOverScene != nullptr)
	{
		score = 0;
		restart = true;
	}
}