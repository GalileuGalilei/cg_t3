#pragma once
#include "gl_canvas2d.h"
#include "Vector2.h"
#include <vector>
#include <CircleCollider.h>
#include <random>


class BezierCurve
{
private:
	std::vector<Vector2> points;

public:
	BezierCurve();
	~BezierCurve();
	void SetControllPoint(Vector2 point, int i);

	void Render(float t);
	void Translate(Vector2 translation);
	bool IsColliding(CircleCollider other);
	void GetBoudingBox(Vector2& min, Vector2& max);
};

