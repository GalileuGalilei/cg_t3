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

	RectCollider bounds = leftCurve[tam - 2]->GetBounds();
	Vector2 start = bounds.size + bounds.position;
	leftCurve[tam - 1] = GenerateRandomCurve(start, direction, range);

	bounds = rightCurve[tam - 2]->GetBounds();
	start = bounds.size + bounds.position;
	rightCurve[tam - 1] = GenerateRandomCurve(start, direction, range);

	leftCurve[tam - 1]->ConnectTailTo(leftCurve[tam - 2]);
	rightCurve[tam - 1]->ConnectTailTo(rightCurve[tam - 2]);
}

Scenary::Scenary(Vector2 leftRange, Vector2 rightRange, Vector2 heightRange)
{
	leftCurve.resize(2);
	rightCurve.resize(2);
	
	Vector2 leftStart = Vector2((leftRange.y + leftRange.x) / 2, heightRange.x);
	Vector2 rightStart = Vector2((rightRange.y + rightRange.x) / 2, heightRange.x);

	this->leftRange = leftRange;
	this->rightRange = rightRange;

	direction = Vector2(0, heightRange.y - heightRange.x);
	range = Vector2((leftRange.y - leftRange.x) / 2, (leftRange.y - leftRange.x) / 2);

	leftCurve[1] = GenerateRandomCurve(leftStart, direction, range);
	rightCurve[1] = GenerateRandomCurve(rightStart, direction, range);
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

BezierCurve* Scenary::GenerateRandomCurve(Vector2 start, Vector2 direction, Vector2 range)
{
	BezierCurve* curve = new BezierCurve();
	float jump = direction.module() / 3;
	Vector2 perpendicular = direction.CalculateLeftPerpendicular();
	Vector2 controllPoint = start;
	Vector2 lastPerpendicular = Vector2(0, 0);

	perpendicular.normalize();
	direction.normalize();
	
	for (int i = 0; i < 4; i++)
	{
		curve->SetControllPoint(controllPoint, i);
		controllPoint -= lastPerpendicular;

		float r = (rand() % (int)range.x) * 2 - range.y;
		lastPerpendicular = perpendicular * r;
		controllPoint += direction * jump;
		controllPoint += lastPerpendicular;
	}

	return curve;
}