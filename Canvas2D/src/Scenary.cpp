#include "Scenary.h"
#include "GameManager.h"
#include <algorithm>

void Scenary::UpdateCurve()
{
	int tam = curve.size();
	delete curve[0];
	for (int i = 0; i < tam - 1; i++)
	{
		curve[i] = curve[i + 1];
	}

	RectCollider bounds = curve[tam - 2]->GetBounds();
	Vector2 start = Vector2(range * 0.5 + border, screenSize.y);
	curve[tam - 1] = GenerateRandomCurve(start, direction, range);
	curve[tam - 1]->ConnectTailTo(curve[tam - 2]);
}

Scenary::Scenary(Vector2 screenSize, float range, float border)
{
	this->screenSize = screenSize;
	this->range = range;
	this->border = border;

	curve.resize(2);
	Vector2 start = Vector2(range / 2, 0 + border);

	direction = Vector2(0, screenSize. y / 2);
	curve[1] = GenerateRandomCurve(start, direction, range);
	UpdateCurve();
}

Scenary::~Scenary()
{
	for (int i = 0; i < curve.size(); i++)
	{
		delete curve[i];
	}
}

void Scenary::OnRender(OnRenderEvent* args)
{
	for (int i = 0; i < curve.size(); i++)
	{
		curve[i]->Render();
		CV::translate(screenSize.x - range - border, 0);
		curve[i]->Render();
		CV::translate(0, 0);
	}

	//move verticalmente as curvas
	Vector2 translation(0, -speed * GameManager::deltaTime);
	Translate(translation);
	RectCollider bounds = curve[curve.size() - 1]->GetBounds();
	if (bounds.position.y + bounds.size.y < screenSize.y)
	{
		UpdateCurve();
	}
		
}

void Scenary::Translate(Vector2 translation)
{
	for (int i = 0; i < curve.size(); i++)
	{
		curve[i]->Translate(translation);
	}
}

BezierCurve* Scenary::GenerateRandomCurve(Vector2 start, Vector2 direction, float range)
{
	BezierCurve* curve = new BezierCurve();
	float jump = direction.lenght() / 3;
	Vector2 perpendicular = direction.GetLeft();
	Vector2 controllPoint = start;
	Vector2 lastPerpendicular = Vector2(0, 0);

	perpendicular.normalize();
	direction.normalize();
	
	for (int i = 0; i < 4; i++)
	{
		curve->SetControllPoint(controllPoint, i);
		controllPoint -= lastPerpendicular;

		float r = ((rand() % 100) / 100.0) * range * 2 - range;
		lastPerpendicular = perpendicular * r * 0.5;
		controllPoint += direction * jump;
		controllPoint += lastPerpendicular;
	}

	return curve;
}