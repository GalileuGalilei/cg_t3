#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "BezierCurve.h"
#include "GameEvents.h"
#include <vector>

/// <summary>
/// classe que gera curvas de bezier proceduralmente que se deslocam para baixo
/// </summary>
class Scenary : IRenderable
{
private:
	std::vector<BezierCurve*> leftCurve;
	std::vector<BezierCurve*> rightCurve;
	Vector2 leftConnection;
	Vector2 rightConnection;

	Vector2 leftRange; //range do eixo x que a curva pode ocupar
	Vector2 rightRange; //range do eixo x que a curva pode ocupar
	Vector2 heightRange; //range do eixo y que a curva pode ocupar
	
	float speed = 200;

	BezierCurve* GenerateRandomCurve(Vector2 heightRange, Vector2 widthRange);
	void UpdateCurves();

public:
	Scenary(Vector2 leftRange, Vector2 rightRange, Vector2 heightRange);
	~Scenary();

	void OnRender(OnRenderEvent* args) override;
	void Translate(Vector2 translation);
};

