#include "Vector2.h"
#include <stdlib.h>

Vector2 Vector2::MinVector = Vector2(-99999, -99999);
Vector2 Vector2::MaxVector = Vector2(99999, 99999);

Vector2 Vector2::Random()
{
    float x = (float)(rand() % 100) / 100;
    float y = (float)(rand() % 100) / 100;
    
    x = 2 * x - 1;
    y = 2 * y - 1;

    Vector2 aux = Vector2(x, y);
    aux.normalize();

	return aux;
}

Vector2::Vector2()
{
    x = y = 0;
}

Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

void Vector2::set(float _x, float _y)
{
    x = _x;
    y = _y;
}

float Vector2::dot(Vector2 other)
{
	return x * other.x + y * other.y;
}

void Vector2::rotate(float angle)
{
	float rad = angle * 3.14159265 / 180.0;
	float c = cos(rad);
	float s = sin(rad);
	float xp = x * c - y * s;
	float yp = x * s + y * c;
	x = xp;
	y = yp;
}

void Vector2::normalize()
{
    float norm = this->length();

    if (norm == 0.0)
    {
        x = 1;
        y = 1;
        return;
    }
    x /= norm;
    y /= norm;
}

float Vector2::length()
{
	return sqrt(x * x + y * y);
}

float Vector2::lengthSqr()
{
    return x * x + y * y;
}

Vector2 Vector2::GetLeft()
{
	return Vector2(-y, x);
}

Vector2 Vector2::GetRight()
{
	return Vector2(y, -x);
}