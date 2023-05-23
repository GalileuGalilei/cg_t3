#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2 position, float radius)
{
	this->position = position;
	this->radius = radius;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::SetPosition(Vector2 position)
{
	this->position = position;
}

void CircleCollider::SetRadius(float radius)
{
	this->radius = radius;
}

bool CircleCollider::IsColliding(CircleCollider other)
{
	float distance = Vector2::distance(position, other.position);
	return distance < radius + other.radius;
}

bool CircleCollider::IsColliding(Vector2 point)
{
	float distance = Vector2::distance(position, point);
	return distance < radius;
}