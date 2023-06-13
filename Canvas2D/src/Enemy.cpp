#include "Enemy.h"
#include "GameManager.h"

Enemy::Enemy(Vector2 position, Vector2 direction, Player* target) : MovableObject("figures/Enemy.gr"), ICollidable(new CircleCollider(position, 25))
{
	this->player = target;
	this->collider = (CircleCollider*)ICollidable::collider;
	this->collider->SetTag("Enemy");

	this->position = position;
	this->speed = direction * 100;
	this->acceleration = direction * 5;

	figure.SetPosition(position);
	figure.SetScale(Vector2(0.45,0.45));
	figure.AlignWith(position - speed);

	GameManager::Instance()->AddEnemy(this);
}

Enemy::~Enemy()
{
	delete collider;
}

void Enemy::OnUpdate(OnUpdateEvent* args)
{
	MovableObject::OnUpdate(args);
	collider->SetPosition(position);
	figure.AlignWith(position * 2 - player->GetPosition());

	timerToShoot += args->deltaTime;

	if (timerToShoot > 1.0)
	{
		timerToShoot = 0.0;
		Shoot();
	}

	Bounds* screen = GameManager::Instance()->screenBounds;
	float dist;
	bool isBellowScreen = !screen->RayCast(position, speed, dist);
	if (isBellowScreen)
	{
		isDestroyed = true;
	}
}

void Enemy::OnCollision(OnCollisionEvent* args)
{
	if (args->collider->GetTag() == "PlayerBullet")
	{
		isDestroyed = true;
		GameManager::Instance()->AddScore(15);
	}
}

bool Enemy::IsDestroyed()
{
	return isDestroyed;
}

void Enemy::Destroy()
{
	isDestroyed = true;
}

void Enemy::Shoot()
{
	Vector2 direction = player->GetPosition() - position;
	direction.normalize();
	new EnemyBullet(position, direction * maxSpeed, direction);
}