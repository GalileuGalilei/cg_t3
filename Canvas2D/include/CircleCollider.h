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

#endif // !CIRCLE_COLLIDER

