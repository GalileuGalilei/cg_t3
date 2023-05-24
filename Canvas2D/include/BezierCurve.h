#pragma once
#include "gl_canvas2d.h"
#include "Vector2.h"
#include <vector>
#include "Colliders.h"
#include <random>


class BezierCurve
{
private:
	std::vector<Vector2> points;
	RectCollider* BoundingBox = nullptr;
	Vector2 CalculateCurvePoint(float t);
	void CalculateBoudingBox(); 

public:
	BezierCurve();
	~BezierCurve();
	void SetControllPoint(Vector2 point, int i);
	RectCollider GetBounds();

	void Render();
	void Translate(Vector2 translation);
	void ConnectTailTo(BezierCurve* other);
	bool IsColliding(CircleCollider other);
};

