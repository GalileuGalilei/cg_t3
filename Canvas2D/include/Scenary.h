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

	Vector2 direction; //direção em que está sendo criado o cenario
	Vector2 range; //o quão próxima da borda da tela são gerados os cenários(curvas)

	Vector2 leftRange;
	Vector2 rightRange;
	
	float speed = 200;

	/// <summary>
	/// cria uma curva de bezier aleatória
	/// </summary>
	/// <param name="start">ponto inicial da curva</param>
	/// <param name="direction">direção da curvá. O modulo desse vetor define o comprimento final da curva</param>
	/// <param name="range">a variação máxima da curva na direção perpendicular ao parametro direction</param>
	BezierCurve* GenerateRandomCurve(Vector2 start, Vector2 direction, Vector2 range);
	void UpdateCurves();

public:
	Scenary(Vector2 leftRange, Vector2 rightRange, Vector2 heightRange);
	~Scenary();

	void OnRender(OnRenderEvent* args) override;
	void Translate(Vector2 translation);
};

