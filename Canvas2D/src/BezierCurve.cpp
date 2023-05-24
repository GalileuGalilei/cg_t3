#include "BezierCurve.h"
#include <math.h>

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

Vector2 BezierCurve::CalculateCurvePoint(float t)
{
	if(t < 0 || t > 1)
		return Vector2(0, 0);

	Vector2 p01 = Lerp(points[0], points[1], t);
	Vector2 p12 = Lerp(points[1], points[2], t);
	Vector2 p23 = Lerp(points[2], points[3], t);
	Vector2 p012 = Lerp(p01, p12, t);
	Vector2 p123 = Lerp(p12, p23, t);
	Vector2 p0123 = Lerp(p012, p123, t);
	return p0123;
}

void BezierCurve::CalculateBoudingBox()
{
	Vector2 max = Vector2::minimun;
	Vector2 min = Vector2::maximun;
	for (float i = 0; i <= 1.0f; i += 0.01)
	{
		Vector2 aux = CalculateCurvePoint(i);
		max = Vector2::max(max, aux);
		min = Vector2::min(min, aux);
	}

	BoundingBox = new RectCollider(min, max - min);
}

RectCollider BezierCurve::GetBounds()
{
	if (BoundingBox == nullptr)
	{
		CalculateBoudingBox();
	}

	return *BoundingBox;
}

void BezierCurve::Render()
{
	Vector2 oldP;
	for (float i = 0; i <= 1.0f; i += 0.01)
	{
		Vector2 p0123 = CalculateCurvePoint(i);

		if (i == 0)
		{
			oldP = p0123;
			continue;
		}

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
		if (BoundingBox != nullptr)
		{
			BoundingBox->center = BoundingBox->center + translation;
			BoundingBox->position = BoundingBox->position + translation;
		}
	}
}

bool BezierCurve::IsColliding(CircleCollider other)
{
	for (float i = 0; i < 1; i += 0.01)
	{
		Vector2 p0123 = CalculateCurvePoint(i);
		if (other.IsColliding(p0123))
			return true;
	}
	return false;
}

