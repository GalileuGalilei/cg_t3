#ifndef MOVABLE_OBJECT
#define MOVABLE_OBJECT
#include "Vector2.h"
#include "GameEvents.h"
#include "Figure.h"
#include <cmath>

class MovableObject : public IUpdatable
{
protected:
	Vector2 position;
	Vector2 speed;
	Vector2 acceleration; //vetor normalizado
	float maxSpeed = 350;
	float maxAcceleration = 1000;
	Figure figure;

	MovableObject(const char path[]);
	void OnUpdate(OnUpdateEvent* args) override;

public:
	Vector2 GetPosition();
	Vector2 GetDirection();
};

#endif // !#define MOVABLE_OBJECT