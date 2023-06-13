#include "Bullet.h"
#include "GameManager.h"

Bullet::Bullet(Vector2 position, Vector2 speed, Vector2 acceleration, const char path[]) : MovableObject(path)
{
	this->position = position;
	this->speed = speed;
	this->acceleration = acceleration;
	this->maxAcceleration = 200.0;
	figure.SetScale(Vector2(0.2, 0.2));
	figure.SetPosition(position);

	collider = new CircleCollider(position, 10);
	collider->SetTag("Bullet");

	GameManager::Instance()->AddBullet(this);
}

Bullet::~Bullet()
{
	delete collider;
}

bool Bullet::IsDestroyed()
{
	return isDestroyed;
}

void Bullet::Destroy()
{
	isDestroyed = true;
}

void Bullet::OnUpdate(OnUpdateEvent* args)
{
	MovableObject::OnUpdate(args);
	figure.AlignWith(position + speed);
	collider->SetPosition(position);
}

EnemyBullet::EnemyBullet(Vector2 position, Vector2 speed, Vector2 acceleration) : 
	Bullet(position, speed, acceleration, "figures/EnemyBullet.gr")
{
	collider->SetTag("EnemyBullet");
	figure.SetScale(Vector2(1.2, 1.2));
}

EnemyBullet::~EnemyBullet()
{

}

PlayerBullet::PlayerBullet(Vector2 position, Vector2 speed, Vector2 acceleration) : 
	Bullet(position, speed, acceleration, "figures/PlayerBullet.gr")
{
	collider->SetTag("PlayerBullet");
}

PlayerBullet::~PlayerBullet()
{

}

TripleBullet::TripleBullet(Vector2 position, Vector2 speed, Vector2 acceleration) :
	Bullet(position, speed, acceleration, "figures/PlayerBullet.gr")
{
	collider->SetTag("PlayerBullet");
}

TripleBullet::~TripleBullet()
{
}

void TripleBullet::OnUpdate(OnUpdateEvent* args)
{
	Bullet::OnUpdate(args);
	figure.AlignWith(position + speed);
	collider->SetPosition(position);
}

CurvedBullet::CurvedBullet(Vector2 position, Vector2 speed, Vector2 acceleration) :
	Bullet(position, speed, acceleration, "figures/PlayerBullet.gr")
{
	collider->SetTag("PlayerBullet");
	maxAcceleration *= 3;
	maxSpeed *= 1.25;

	Vector2 direction = speed;
	direction.normalize();
	Vector2 left = Vector2(-direction.y, direction.x) + direction;
	Vector2 right = Vector2(direction.y, -direction.x) + direction;

	Vector2 newspeed;
	Vector2 newacceleration;

	if (rand() % 2 == 0)
	{
		newacceleration = left * 2;
		newspeed = right * speed.length() * 0.75;
	}
	else
	{
		newacceleration = right * 2;
		newspeed = left * speed.length() * 0.75;
	}

	this->speed = newspeed;
	this->acceleration = newacceleration;

	this->position += direction * 50;
	figure.SetPosition(this->position);
}

CurvedBullet::~CurvedBullet()
{

}