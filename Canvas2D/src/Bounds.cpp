#include "Bounds.h"
#include <cmath>
#include <algorithm>

Bounds::Bounds(float x, float y, float w, float h)
{
	position = Vector2(x, y);
	size = Vector2(w, h);
	center = position + size / 2;
}

Bounds::Bounds(Vector2 position, Vector2 size)
{
	this->position = position;
	this->size = size;
	center = position + size / 2;
}

bool Bounds::Contains(Vector2 point)
{
	Vector2 min = position;
	Vector2 max = position + size;
	return (point.x >= min.x &&
					point.x <= max.x &&
					point.y >= min.y &&
					point.y <= max.y);
}

bool Bounds::Intersects(Bounds& other)
{
	Vector2 min = position;
	Vector2 max = position + size;
	Vector2 otherMin = other.position;
	Vector2 otherMax = other.position + other.size;
	return (min.x <= otherMax.x &&
        					max.x >= otherMin.x &&
        					min.y <= otherMax.y &&
        					max.y >= otherMin.y);
}

bool Bounds::RayCast(Vector2 origin, Vector2 direction, float& distance)
{
    direction.normalize();

    // Calculate the ray's endpoint (assume it extends infinitely in the direction)
    float endX = origin.x + direction.x;
    float endY = origin.y + direction.y;

    // Calculate the ray's intersection with the rectangle's sides
    float t;
    float tMin = std::numeric_limits<float>::min(); // Smallest possible float value
    float tMax = std::numeric_limits<float>::max(); // Largest possible float value

    // Check the intersection with vertical sides
    if (direction.x != 0.0f) {
        float t1 = (position.x - origin.x) / direction.x;
        float t2 = (position.x + size.x - origin.x) / direction.x;
        tMin = std::max(tMin, std::min(t1, t2));
        tMax = std::min(tMax, std::max(t1, t2));
    }

    // Check the intersection with horizontal sides
    if (direction.y != 0.0f) {
        float t1 = (position.y - origin.y) / direction.y;
        float t2 = (position.y + size.y - origin.y) / direction.y;
        tMin = std::max(tMin, std::min(t1, t2));
        tMax = std::min(tMax, std::max(t1, t2));
    }

    // Check if the ray intersects the rectangle
    if (tMax >= tMin && tMax >= 0.0f) {
        distance = tMin;
        return true;
    }
    else {
        distance = 0.0f;
        return false;
    }
}

bool Bounds::RayCast(Vector2 origin, Vector2 direction, float rayWidth, float& distance)
{
    direction.normalize();
    origin += direction.GetLeft() * rayWidth / 2;

    if (this->RayCast(origin, direction, distance))
        return true;

    origin -= direction.GetLeft() * rayWidth;
    return this->RayCast(origin, direction, distance);
}

