#include "Scenary.h"
#include "GameManager.h"
#include "PowerUp.h"
#include <algorithm>

Scenary::Scenary(Vector2 screenSize, float range, float border) : screenBounds(Vector2(0, 0), screenSize)
{
	this->range = range;
	this->border = border;
	this->curvesLenght = 300;
	this->direction = Vector2::Random();
	this->direction.normalize();
	this->SetTag("Scenary");
	curve.resize(6);

	Vector2 start = CalculateStartPoint(nullptr);

	for (int i = 0; i < curve.size(); i++)
	{
		curve[i] = GenerateRandomCurve(start, direction, curvesLenght, range);
		start = CalculateStartPoint(curve[i]);

		if (i != 0)
		{
			curve[i]->ConnectTailTo(curve[i - 1]);
		}
	}
}

Scenary::~Scenary()
{
	for (int i = 0; i < curve.size(); i++)
	{
		delete curve[i];
	}
}

float DistanceToLine(Vector2 point, Vector2 lineStart, Vector2 lineEnd)
{
	Vector2 line = lineEnd - lineStart;
	Vector2 pointToLine = point - lineStart;
	float dot = pointToLine.dot(line);
	float lineLenght = line.length();
	float dist = dot / lineLenght;
	return dist;
}

bool Scenary::IsColliding(Vector2 point)
{
	for(BezierCurve* c : curve)
	{
		for (float i = 0; i < 1; i += 0.04)
		{
			Vector2 a1 = c->CalculateCurvePoint(i);
			Vector2 a2 = c->CalculateCurvePoint(i + 0.1);

			float dist1 = DistanceToLine(point, a1, a2);
			
			Vector2 t = direction.GetRight() * (screenBounds.size.x - range - border * 2);
			a1 += t;
			a2 += t;

			float dist2 = DistanceToLine(point, a1, a2);

			if (dist1 < 1 || dist2 < 1)
			{
				return true;
			}
		}
	}

	return false;
}

bool Scenary::IsColliding(ICollider* other, Vector2& collisionPoint)
{
	Vector2 point = other->GetCenter();

	if (point.x > screenBounds.size.x)
	{
		collisionPoint = Vector2(screenBounds.size.x + 10, point.y);
		return true;
	}

	if (point.x < 0)
	{
		collisionPoint = Vector2(-10, point.y);
		return true;
	}

	if (point.y > screenBounds.size.y)
	{
		collisionPoint = Vector2(point.x, screenBounds.size.y + 10);
		return true;
	}

	if (point.y < 0)
	{
		collisionPoint = Vector2(point.x, -10);
		return true;
	}

	for (BezierCurve* c : curve)
	{
		for (float i = 0; i < 1; i += 0.01)
		{
			Vector2 p1 = c->CalculateCurvePoint(i);
			
			if (other->IsColliding(p1))
			{
				collisionPoint = p1;
				return true;
			}

			Vector2 p2 = p1 + direction.GetRight() * (screenBounds.size.x - range - border * 2);

			if (other->IsColliding(p2))
			{
				collisionPoint = p2;
				return true;
			}
		}
	}

	return false;
}

Vector2 Scenary::GetCenter()
{
	return screenBounds.center;
}

void Scenary::SetCurvesLenght(float lenght)
{
	this->curvesLenght = lenght;
}

void Scenary::SetRange(float range)
{
	this->range = range;
}

void Scenary::SetDirection(Vector2 direction)
{
	this->direction = direction;
	this->direction.normalize();
}

void Scenary::SetSpeed(float speed)
{
	this->speed = speed;
}

Vector2 Scenary::CalculateStartPoint(BezierCurve* prevCurve)
{
	
	Vector2 borderDisp = direction.GetLeft() * (screenBounds.center.x - border - range * 0.5);
	Vector2 center = screenBounds.center + borderDisp;
	float dist;
	screenBounds.RayCast(center, direction, dist);
	Vector2 start = center;

	if (prevCurve != nullptr)
	{
		Bounds prevCurveBound = prevCurve->GetBounds();
		float offset = 15;
		bool outOfRange = !prevCurveBound.RayCast(start, direction, offset, dist);

		if (outOfRange)
		{
			dist = curvesLenght * 2;
		}

		start += direction * (dist + curvesLenght);
	}
	else
	{
		start += direction * dist;
	}

	return start;
}


void Scenary::UpdateCurve()
{
	int tam = curve.size();
	delete curve[0];
	for (int i = 0; i < tam - 1; i++)
	{
		curve[i] = curve[i + 1];
	}

	Vector2 start = CalculateStartPoint(curve[tam - 2]);
	curve[tam - 1] = GenerateRandomCurve(start, direction, curvesLenght, range);
	curve[tam - 1]->ConnectTailTo(curve[tam - 2]);
}

void Scenary::OnRender(OnRenderEvent* args)
{
	if (!isRenderEnabled)
	{
		return;
	}

	for (int i = 0; i < curve.size(); i++)
	{

#ifdef DEBUG

		curve[i]->Render();
	//	CV::rect(border, 0, border + range, screenSize.y);
		RectCollider b1 = curve[i]->GetBounds();
		CV::color(0, 0, 1);
		CV::rect(b1.position, b1.position + b1.size);
		CV::color(1, 0, 0);
		CV::translate(direction.GetRight() * (screenBounds.size.x - range - border * 2));
	//	CV::rect(border, 0, border + range, screenSize.y);
		CV::color(0, 0, 1);
		CV::rect(b1.position, b1.position + b1.size);
		CV::color(1, 0, 0);
		curve[i]->Render();
		CV::translate(0, 0);
 
#else
		curve[i]->Render();
		CV::translate(direction.GetRight() * (screenBounds.size.x - range - border * 2));
		curve[i]->Render();
		CV::translate(0, 0);
#endif
	}

	//move verticalmente as curvas
	Vector2 translation = direction * ( - GameManager::deltaTime) * speed;
	Translate(translation);

	//verifica se a primeira curva saiu da tela
	Bounds bounds = curve[0]->GetBounds();
	float dist;
	bool isBellowScreen = !screenBounds.RayCast(bounds.center, translation, dist);

	if (!screenBounds.Intersects(bounds) && isBellowScreen)
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

BezierCurve* Scenary::GenerateRandomCurve(Vector2 start, Vector2 direction, float lenght, float range)
{
	BezierCurve* curve = new BezierCurve();
	float jump = lenght / 3;
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

void Scenary::SpawnEnemy(Player* target)
{
	Vector2 spawnPoint = screenBounds.center;
	float dist = 400;
	spawnPoint += direction * dist;
	spawnPoint += direction.GetLeft() * (rand() % 400 - 200);
	Enemy* enemy = new Enemy(spawnPoint, direction * (-1), target);
}

void Scenary::SpawnPowerUp()
{
	Vector2 spawnPoint = screenBounds.center;
	float dist = 400;
	spawnPoint += direction * dist;
	spawnPoint += direction.GetLeft() * (rand() % 200 - 100);

	int type = rand() % 2;

	switch (type)
	{
	case 0:
		new CurvedBulletPowerUp(spawnPoint, direction * (-1));
		break;

	case 1:
		new TripleBulletPowerUp(spawnPoint, direction * (-1));
		break;

	default:
		break;
	}
}

void Scenary::SetRender(bool state)
{
	this->isRenderEnabled = state;
}