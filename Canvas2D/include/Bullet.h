#ifndef BULLET
#define BULLET
#include "MovableObject.h"
#include "Colliders.h"
#include "Enemy.h"


class Bullet : public MovableObject
{
protected:
	bool isDestroyed = false;

public:
	CircleCollider* collider;


	bool IsDestroyed();
	void Destroy();

	void OnUpdate(OnUpdateEvent* args) override;

	Bullet(Vector2 position, Vector2 speed, Vector2 acceleration, const char path[]);
	~Bullet();
};

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(Vector2 position, Vector2 speed, Vector2 acceleration);
	~EnemyBullet();
};

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(Vector2 position, Vector2 speed, Vector2 acceleration);
	~PlayerBullet();
};

class TripleBullet : public Bullet
{
private:
	void OnUpdate(OnUpdateEvent* args) override;

public:
	TripleBullet(Vector2 position, Vector2 speed, Vector2 acceleration);
	~TripleBullet();
};

class CurvedBullet : public Bullet
{
public:
	CurvedBullet(Vector2 position, Vector2 speed, Vector2 acceleration);
	~CurvedBullet();

};

#endif // !BULLET