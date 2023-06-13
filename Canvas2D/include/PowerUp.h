#ifndef POWER_UP
#define POWER_UP

#include "GameEvents.h"
#include "Colliders.h"
#include "MovableObject.h"

class PowerUp : public MovableObject, public ICollidable
{
protected:
	CircleCollider* collider;

public:
	bool isDestroyed = false;
	bool IsDestroyed();
	void Destroy();


	PowerUp(Vector2 position, Vector2 direction, const char path[]);
	~PowerUp();
	void OnUpdate(OnUpdateEvent* args) override;

	void OnCollision(OnCollisionEvent* args);
};


class TripleBulletPowerUp : PowerUp
{
public:
	TripleBulletPowerUp(Vector2 position, Vector2 direction);
	~TripleBulletPowerUp();
};

class CurvedBulletPowerUp : PowerUp
{
public:
	CurvedBulletPowerUp(Vector2 position, Vector2 direction);
	~CurvedBulletPowerUp();
};;

#endif // !POWER_UP
