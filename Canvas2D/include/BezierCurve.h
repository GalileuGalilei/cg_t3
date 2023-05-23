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

	void Render();
	void Translate(Vector2 translation);
	void ConnectTailTo(BezierCurve* other);
	bool IsColliding(CircleCollider other);
	Vector2 min, max;
};

