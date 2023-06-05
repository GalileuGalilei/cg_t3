#include "Colliders.h"

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

RectCollider::RectCollider(float x, float y, float w, float h)
{
    position.x = x;
    position.y = y;
    size.x = w;
    size.y = h;

    center.x = x + w / 2;
    center.y = y + h / 2;
}

RectCollider::RectCollider(Vector2 position, Vector2 size)
{
    this->position = position;
    this->size = size;
    center = position + size / 2;
}

bool RectCollider::IsColliding(Vector2 point)
{
    Vector2 min = position;
    Vector2 max = position + size;
    if (point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y)
    {
        return true;
    }
}
