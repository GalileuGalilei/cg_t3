#ifndef SCENARY
#define SCENARY

#include <vector>
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "BezierCurve.h"
#include "Colliders.h"
#include "Enemy.h"

/// <summary>
/// classe que gera curvas de bezier proceduralmente que se deslocam para baixo
/// </summary>
class Scenary : IRenderable, public ICollider
{
private:
	std::vector<BezierCurve*> curve;

	Vector2 direction; //direção em que está sendo criado o cenario
	float speed = 220;

	Bounds screenBounds;
	float range;
	float border;
	float curvesLenght;

	bool testRotate = false;
	bool isRenderEnabled = true;

	/// <summary>
	/// cria uma curva de bezier aleatória
	/// </summary>
	/// <param name="start">ponto inicial da curva</param>
	/// <param name="direction">direção da curvá. O modulo desse vetor define o comprimento final da curva</param>
	/// <param name="range">a variação máxima da curva na direção perpendicular ao parametro direction</param>
	/// <param name="lenght">o comprimento da curva</param>
	BezierCurve* GenerateRandomCurve (Vector2 start, Vector2 direction, float lenght, float range);

	/// <summary>
	/// deleta a curva mais antiga e cria uma nova
	/// </summary>
	void UpdateCurve();

	Vector2 CalculateStartPoint(BezierCurve* prevCurve);
	void Translate(Vector2 translation);

public:
	Scenary(Vector2 screenSize, float range, float border);
	~Scenary();

	bool IsColliding(Vector2 point) override;
	bool IsColliding(ICollider* other, Vector2& collisionPoint) override;
	Vector2 GetCenter() override;
	void OnRender(OnRenderEvent* args) override;

	void SetDirection(Vector2 direction);
	void SetSpeed(float speed);
	void SetRange(float range);
	void SetCurvesLenght(float lenght);
	void SpawnEnemy(Player* target);
	void SpawnPowerUp();
	void SetRender(bool state);
};


#endif // !SCENARY