#include "PowerUp.h"
#include "GameManager.h"

bool PowerUp::IsDestroyed()
{
	return isDestroyed;
}

void PowerUp::Destroy()
{
	isDestroyed = true;
}

PowerUp::PowerUp(Vector2 position, Vector2 direction, const char path[]) : MovableObject(path), ICollidable(new CircleCollider(position, 100))
{
	collider = (CircleCollider*)ICollidable::collider;
	collider->SetTag("PowerUp");
	this->position = position;
	this->speed = direction * 100;
	this->acceleration = direction * 5;

	GameManager::Instance()->AddPowerUp(this);
}

PowerUp::~PowerUp()
{
	delete collider;
}

void PowerUp::OnUpdate(OnUpdateEvent* args)
{
	MovableObject::OnUpdate(args);
	collider->SetPosition(position);
}

void PowerUp::OnCollision(OnCollisionEvent* args)
{
	if (args->collider->GetTag() == "Player")
	{
		isDestroyed = true;
	}
}

TripleBulletPowerUp::TripleBulletPowerUp(Vector2 position, Vector2 direction) : PowerUp(position, direction, "figures/tripleBulletPowerUp.gr")
{
	figure.SetScale(Vector2(0.5, 0.5));
	collider->SetTag("tripleBulletPowerUp");
}

TripleBulletPowerUp::~TripleBulletPowerUp()
{

}

CurvedBulletPowerUp::CurvedBulletPowerUp(Vector2 position, Vector2 direction) : PowerUp(position, direction, "figures/curveBulletPowerUp.gr")
{
	figure.SetScale(Vector2(0.5, 0.5));
	collider->SetTag("curvedBulletPowerUp");
}

CurvedBulletPowerUp::~CurvedBulletPowerUp()
{

}
