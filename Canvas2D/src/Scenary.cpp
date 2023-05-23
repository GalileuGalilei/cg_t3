#include "Scenary.h"

Scenary::Scenary(Vector2 leftRange, Vector2 rightRange, Vector2 heightRange)
{
	this->leftRange = leftRange;
	this->rightRange = rightRange;
	this->heightRange = heightRange;

	leftCurve.resize(2);
	rightCurve.resize(2);

	leftCurve[0] = GenerateRandomCurve(true);
	leftCurve[1] = GenerateRandomCurve(true);

	rightCurve[0] = GenerateRandomCurve(false);
	rightCurve[1] = GenerateRandomCurve(false);
}

Scenary::~Scenary()
{
}

void Scenary::Render(float t)
{
	for (int i = 0; i < leftCurve.size(); i++)
	{
		leftCurve[i]->Render(t);
		rightCurve[i]->Render(t);
	}

	//move verticalmente as curvas
	Vector2 translation(0, -speed);
	Translate(translation);
}

void Scenary::Translate(Vector2 translation)
{
	for (int i = 0; i < leftCurve.size(); i++)
	{
		leftCurve[i]->Translate(translation);
		rightCurve[i]->Translate(translation);
	}
}

BezierCurve* Scenary::GenerateRandomCurve(bool left)
{
	BezierCurve* curve = new BezierCurve();
	
	for (int i = 0; i < 4; i++)
	{
		float randX = rand() % (int)((left ? leftRange.y : rightRange.y) + 1);
		float randY = rand() % (int)(heightRange.y + 1);
		curve->SetControllPoint(Vector2(randX, randY), i);
	}

	return curve;
}