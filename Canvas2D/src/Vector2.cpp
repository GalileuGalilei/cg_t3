#include "Vector2.h"

Vector2 Vector2::MinVector = Vector2(-99999, -99999);
Vector2 Vector2::MaxVector = Vector2(99999, 99999);

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

void Vector2::normalize()
{
    float norm = this->lenght();

    if (norm == 0.0)
    {
        x = 1;
        y = 1;
        return;
    }
    x /= norm;
    y /= norm;
}

float Vector2::lenght()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::GetLeft()
{
	return Vector2(-y, x);
}

Vector2 Vector2::GetRight()
{
	return Vector2(y, -x);
}