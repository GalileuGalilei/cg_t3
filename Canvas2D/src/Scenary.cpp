#include "Scenary.h"
#include "GameManager.h"
#include <algorithm>

void Scenary::UpdateCurves()
{
	int tam = leftCurve.size();
	for (int i = 0; i < tam - 1; i++)
	{
		leftCurve[i] = leftCurve[i + 1];
		rightCurve[i] = rightCurve[i + 1];
	}

	Vector2 max;
	max = leftCurve[tam - 2]->max;
	Vector2 newHeightRange = heightRange;
	newHeightRange.x += max.y;
	newHeightRange.y += max.y;

	leftCurve[tam - 1] = GenerateRandomCurve(newHeightRange, leftRange);
	rightCurve[tam - 1] = GenerateRandomCurve(newHeightRange, rightRange);
}

Scenary::Scenary(Vector2 leftRange, Vector2 rightRange, Vector2 heightRange)
{
	this->leftRange = leftRange;
	this->rightRange = rightRange;
	this->heightRange = heightRange;

	leftCurve.resize(2);
	rightCurve.resize(2);

	leftCurve[1] = GenerateRandomCurve(heightRange, leftRange);
	rightCurve[1] = GenerateRandomCurve(heightRange, rightRange);
	UpdateCurves();
}

Scenary::~Scenary()
{
}

void Scenary::OnRender(OnRenderEvent* args)
{
	for (int i = 0; i < leftCurve.size(); i++)
	{
		leftCurve[i]->Render();
		rightCurve[i]->Render();
	}

	//move verticalmente as curvas
	Vector2 translation(0, -speed * GameManager::deltaTime);
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

BezierCurve* Scenary::GenerateRandomCurve(Vector2 heightRange, Vector2 widthRange)
{
	BezierCurve* curve = new BezierCurve();
	int heightOffset = (heightRange.y - heightRange.x) / 3;
	int currentHeight = heightRange.x;
	int widthOffset = (int)(widthRange.y - widthRange.x);
	float randX = 0, randY = 0;
	
	for (int i = 0; i < 4; i++)
	{
		randX = rand() % (int)(widthOffset) + widthRange.x;
		randY = currentHeight;
		curve->SetControllPoint(Vector2(randX, randY), i);
		currentHeight += heightOffset;
	}

	return curve;
}