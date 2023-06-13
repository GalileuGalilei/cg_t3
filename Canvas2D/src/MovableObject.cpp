#include "MovableObject.h"

MovableObject::MovableObject(const char path[])
{
	figure.LoadFigure(path);
	position = Vector2(0, 0);
	speed = Vector2(0, 0);
	acceleration = Vector2(0, 0);
	figure.SetPosition(position);
}

void MovableObject::OnUpdate(OnUpdateEvent* args)
{
	if(std::abs(acceleration.x) > 0.5 || std::abs(acceleration.y) > 0.5)
		speed += acceleration * maxAcceleration * args->deltaTime;

	if (speed.length() > maxSpeed)
	{
		speed.normalize();
		speed = speed * maxSpeed;
	}

	if (std::abs(acceleration.x) < 0.5 && speed.lengthSqr() > 1)
	{
		int dir = speed.x > 0 ? 2 : -2;
		speed.x -= dir * maxAcceleration * args->deltaTime;
	}

	if (std::abs(acceleration.y) < 0.5 && speed.lengthSqr() > 1)
	{
		int dir = speed.y > 0 ? 2 : -2;
		speed.y -= dir * maxAcceleration * args->deltaTime;
	}

	
	position += speed * args->deltaTime;
	figure.SetPosition(position);
	
}

Vector2 MovableObject::GetPosition()
{
	return position;
}

Vector2 MovableObject::GetDirection()
{
	Vector2 aux = speed;
	aux.normalize();
	return aux;
}