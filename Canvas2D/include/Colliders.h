#ifndef CIRCLE_COLLIDER
#define CIRCLE_COLLIDER

#include "Vector2.h"

class CircleCollider
{
public:
	Vector2 position;
	float radius;

	CircleCollider(Vector2 position, float radius);
	~CircleCollider();

	void SetPosition(Vector2 position);
	void SetRadius(float radius);
	bool IsColliding(CircleCollider other);
	bool IsColliding(Vector2 point);
};

class RectCollider
{
public:
    Vector2 position, center, size;

    RectCollider(float x, float y, float w, float h);

    RectCollider(Vector2 position, Vector2 size);

    bool DoesIntersects(Vector2 point);
};

#endif // !CIRCLE_COLLIDER

