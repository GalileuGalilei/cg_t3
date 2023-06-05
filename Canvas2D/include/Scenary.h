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
	std::vector<BezierCurve*> curve;

	Vector2 direction; //dire��o em que est� sendo criado o cenario
	float speed = 200;

	Vector2 screenSize;
	float range;
	float border;

	/// <summary>
	/// cria uma curva de bezier aleat�ria
	/// </summary>
	/// <param name="start">ponto inicial da curva</param>
	/// <param name="direction">dire��o da curv�. O modulo desse vetor define o comprimento final da curva</param>
	/// <param name="range">a varia��o m�xima da curva na dire��o perpendicular ao parametro direction</param>
	BezierCurve* GenerateRandomCurve(Vector2 start, Vector2 direction, float range);
	void UpdateCurve();

public:
	Scenary(Vector2 screenSize, float range, float border);
	~Scenary();

	void OnRender(OnRenderEvent* args) override;
	void Translate(Vector2 translation);
};

