#include "Colliders.h"
#include <type_traits>
#include <cmath>
#include <algorithm>

EventType OnCollisionEvent::GetStaticType()
{
	return EventType::CollisionEvent;
}

std::list<ICollider*> ICollider::collidersList;

ICollider::ICollider()
{
	collidersList.push_back(this);
    tag.assign("default");
}

ICollider::~ICollider()
{
	collidersList.remove(this);
}

void ICollider::SetTag(const char tag[])
{
	this->tag.assign(tag);

}

std::string ICollider::GetTag()
{
    return tag;
}

std::list<ICollidable*> ICollidable::collidablesList;

void ICollidable::TestColissionAll(BaseEvent* baseEvent)
{
    for (ICollidable* c : collidablesList)
    {
        ICollider* collidable = (ICollider*)c;
        for (ICollider* other : collidersList)
        {
            Vector2 collisionPoint;
            if (collidable != other && c->collider != other && other->IsColliding(collidable, collisionPoint))
            {
                OnCollisionEvent args(other, collisionPoint);
				c->OnCollision(&args);
			}
		}
	}
}

bool ICollidable::IsColliding(Vector2 point)
{
	return collider->IsColliding(point);
}

bool ICollidable::IsColliding(ICollider* other, Vector2& collisionPoint)
{
    if (other == collider)
    {
		return false;
	}

    return collider->IsColliding(other, collisionPoint);
}

Vector2 ICollidable::GetCenter()
{
	return collider->GetCenter();
}

ICollidable::ICollidable(ICollider* collider)
{
    this->collider = collider;
	collidablesList.push_back(this);
}

ICollidable::~ICollidable()
{
    collidersList.remove(this->collider);
	collidablesList.remove(this);
}

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

Vector2 CircleCollider::GetCenter()
{
	return position;
}

bool CircleCollider::IsColliding(CircleCollider& other)
{
    float dist = Vector2::distance(position, other.position);
    return dist < radius + other.radius;
}

bool CircleCollider::IsColliding(Vector2 point)
{
	float distance = Vector2::distance(position, point);
	return distance < radius;
}

bool CircleCollider::IsColliding(ICollider* other, Vector2& collisionPoint)
{
    if (other->IsColliding(position))
    {
        collisionPoint = position;
        return true;
    }

    if (IsColliding(other->GetCenter()))
    {
        collisionPoint = position;
        return true;
    }

    return false;
}

RectCollider::RectCollider(float x, float y, float w, float h) : bounds(x, y, w, h)
{

}

RectCollider::RectCollider(Vector2 position, Vector2 size) : bounds(position, size)
{

}

Vector2 RectCollider::GetCenter()
{
	return bounds.position + bounds.size / 2;
}

bool RectCollider::IsColliding(Vector2 point)
{
    return bounds.Contains(point);
}

bool RectCollider::IsColliding(RectCollider& other)
{
    Vector2 min = bounds.position;
	Vector2 max = bounds.position + bounds.size;
	Vector2 otherMin = other.bounds.position;
	Vector2 otherMax = other.bounds.position + other.bounds.size;
	return (min.x <= otherMax.x &&
        	max.x >= otherMin.x &&
        	min.y <= otherMax.y &&
        	max.y >= otherMin.y);
}



bool RectCollider::IsColliding(ICollider* other, Vector2& collisionPoint)
{
    Vector2 position = bounds.position;
    Vector2 size = bounds.size;
    Vector2 point = other->GetCenter();

    if (IsColliding(point))
    {
        float dx = std::abs(point.x - bounds.center.x);
        float dy = std::abs(point.y - bounds.center.y);

        if (dx < dy) //mais perto da vertical
        {
            collisionPoint = Vector2(bounds.center.x, point.y);
        }
		else //mais perto da horizontal
		{
            collisionPoint = Vector2(point.x, bounds.center.y);
        }

        return true;
	}

	return false;


}
