#ifndef ENEMY
#define ENEMY

#include "MovableObject.h"
#include "Colliders.h"
#include "Player.h"

class Enemy : public MovableObject, ICollidable
{
protected:
	bool isDestroyed = false;
	float timerToShoot = 0.0;
	CircleCollider* collider;
	Player* player;

	void OnCollision(OnCollisionEvent* args) override;
	void OnUpdate(OnUpdateEvent* args) override;

public:
	bool IsDestroyed();
	void Destroy();
	void Shoot();

	Enemy(Vector2 position, Vector2 direction, Player* target);
	~Enemy();

};

#endif // !ENEMY

