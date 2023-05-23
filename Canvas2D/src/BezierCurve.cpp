#include "BezierCurve.h"

float Lerp(float a, float b, float x)
{
		return a + x * (b - a);
}

Vector2 Lerp(Vector2 a, Vector2 b, float x)
{
	return Vector2(Lerp(a.x, b.x, x), Lerp(a.y, b.y, x));
}

BezierCurve::BezierCurve()
{
	points.resize(4);
	min = Vector2(FLT_MAX, FLT_MAX);
	max = Vector2(-FLT_MAX, -FLT_MAX);
	Render();
}

BezierCurve::~BezierCurve()
{

}

void BezierCurve::SetControllPoint(Vector2 point, int i)
{
	if (i < 0 || i > 3)
		return;
	points[i] = point;
}

void BezierCurve::ConnectTailTo(BezierCurve* other)
{
	Vector2 p2 = other->points[2];
	Vector2 p3 = other->points[3];
	Vector2 dir = p3 - p2;
	this->points[0] = p3;
	this->points[1] = p3 + dir;
}

void BezierCurve::Render()
{
	Vector2 p0 = points[0];
	Vector2 p1 = points[1];
	Vector2 p2 = points[2];
	Vector2 p3 = points[3];
	Vector2 oldP;
	for (float i = 0; i <= 1.0f; i += 0.01)
	{
		Vector2 p01 = Lerp(p0, p1, i);
		Vector2 p12 = Lerp(p1, p2, i);
		Vector2 p23 = Lerp(p2, p3, i);
		Vector2 p012 = Lerp(p01, p12, i);
		Vector2 p123 = Lerp(p12, p23, i);
		Vector2 p0123 = Lerp(p012, p123, i);

		if (i == 0)
		{
			oldP = p0123;
			continue;
		}

		if (p0123.x < min.x)
			min.x = p0123.x;
		if (p0123.y < min.y)
			min.y = p0123.y;
		if (p0123.x > max.x)
			max.x = p0123.x;
		if (p0123.y > max.y)
			max.y = p0123.y;

		CV::color(255, 0, 0);
		CV::line(oldP.x, oldP.y, p0123.x, p0123.y);
		oldP = p0123;

	}
}

void BezierCurve::Translate(Vector2 translation)
{
	for (int i = 0; i < 4; i++)
	{
		points[i] = points[i] + translation;
	}
}

bool BezierCurve::IsColliding(CircleCollider other)
{
	for (float i = 0; i < 1; i += 0.01)
	{
		Vector2 p0 = points[0];
		Vector2 p1 = points[1];
		Vector2 p2 = points[2];
		Vector2 p3 = points[3];
		Vector2 p01 = Lerp(p0, p1, i);
		Vector2 p12 = Lerp(p1, p2, i);
		Vector2 p23 = Lerp(p2, p3, i);
		Vector2 p012 = Lerp(p01, p12, i);
		Vector2 p123 = Lerp(p12, p23, i);
		Vector2 p0123 = Lerp(p012, p123, i);
		if (other.IsColliding(p0123))
			return true;
	}
	return false;
}

