#pragma once
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "Bounds.h"
#include <vector>
#include <random>


class BezierCurve
{
private:
	std::vector<Vector2> points;
	Bounds boundingBox;
	bool isBoundsCalculated = false;
	void CalculateBoudingBox(); 

public:
	BezierCurve();
	~BezierCurve();
	void SetControllPoint(Vector2 point, int i);
	Bounds GetBounds();

	void Render();
	void Translate(Vector2 translation);
	void ConnectTailTo(BezierCurve* other);
	Vector2 CalculateCurvePoint(float t);
};

