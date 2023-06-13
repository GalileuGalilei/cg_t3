#ifndef COLLIDERS
#define COLLIDERS

#include <list>
#include "Bounds.h"
#include "GameEvents.h"
#include <string>

/// <summary>
/// Classe que pode colidir com outras classes que herdam de ICollidable ou ICollider
/// </summary>
class ICollider
{
protected:
	static std::list<ICollider*> collidersList;
	std::string tag;
	ICollider();
	~ICollider();

public:
	//não há garantias de que isso funcione com qualquer tipo de collider
	virtual bool IsColliding(ICollider* other, Vector2& collisionPoint) = 0;
	virtual bool IsColliding(Vector2 point) = 0;
	virtual Vector2 GetCenter() = 0;

	void SetTag(const char tag[]);
	std::string GetTag();
};

class OnCollisionEvent : public BaseEvent
{
public:
	static EventType GetStaticType();

	EventType GetType() const override
	{
		return GetStaticType();
	}

	ICollider* collider;
	Vector2 collisionPoint;

	OnCollisionEvent(ICollider* collider, Vector2 collisionPoint)
	{
		this->collider = collider;
		this->collisionPoint = collisionPoint;
	}
};

/// <summary>
/// Classe que possui uma callback de colisão para ser chamada quando colidir com outra classe que herda de ICollidable ou ICollider
/// </summary>
class ICollidable : public ICollider
{
private:
	static std::list<ICollidable*> collidablesList;

	bool IsColliding(Vector2 point) override;
	bool IsColliding(ICollider* other, Vector2& collisionPoint) override;
	Vector2 GetCenter() override;

protected:
	ICollider* collider;
	virtual void OnCollision(OnCollisionEvent* args) = 0;
	ICollidable(ICollider* collider);
	~ICollidable();

public:
	static void TestColissionAll(BaseEvent* baseEvent);
};

class CircleCollider : public ICollider
{
public:
	Vector2 position;
	float radius;

	CircleCollider(Vector2 position, float radius);
	~CircleCollider();

	void SetPosition(Vector2 position);
	void SetRadius(float radius);

	bool IsColliding(CircleCollider & other);
	bool IsColliding(ICollider* other, Vector2& collisionPoint) override;
	bool IsColliding(Vector2 point) override;
	Vector2 GetCenter() override;
};

class RectCollider : public ICollider
{
public:
    Bounds bounds;

    RectCollider(float x, float y, float w, float h);
    RectCollider(Vector2 position, Vector2 size);

	bool IsColliding(RectCollider& other);
	bool IsColliding(ICollider* other, Vector2& collisionPoint) override;
	bool IsColliding(Vector2 point) override;
	Vector2 GetCenter() override;
};

#endif // !COLLIDERS

