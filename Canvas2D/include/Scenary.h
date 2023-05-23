#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "BezierCurve.h"
#include <vector>

/// <summary>
/// classe que gera curvas de bezier proceduralmente que se deslocam para baixo
/// </summary>
class Scenary
{
private:
	std::vector<BezierCurve*> leftCurve;
	std::vector<BezierCurve*> rightCurve;

	Vector2 leftRange; //range do eixo x que a curva pode ocupar
	Vector2 rightRange; //range do eixo x que a curva pode ocupar
	Vector2 heightRange; //range do eixo y que a curva pode ocupar
	
	const float speed = 0.1f;

	BezierCurve* GenerateRandomCurve(bool left);

public:
	Scenary(Vector2 leftRange, Vector2 rightRange, Vector2 heightRange);
	~Scenary();

	void Render(float t);
	void Translate(Vector2 translation);
};

