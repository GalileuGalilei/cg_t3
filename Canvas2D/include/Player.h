#ifndef PLAYER
#define PLAYER
#include "MovableObject.h"
#include "Colliders.h"
#include "LifeBar.h"
#include <string>

class Player : public MovableObject, IKeyable, IClickable, ICollidable
{
private:

	bool isDestroyed = false;
	float powerUpTimer = 0;
	std::string powerUp = "default";
	Vector2 mousePosition = Vector2(0, 0);
	CircleCollider* collider;
	LifeBar* lifeBar;

	void OnKey(OnKeyEvent* args) override;
	void OnClick(OnClickEvent* args) override;
	void OnMouseOver(OnMouseOverEvent* args) override;
	void OnUpdate(OnUpdateEvent* args) override;
	void OnCollision(OnCollisionEvent* args) override;

public:
	Player();
	~Player();
	bool IsDestroyed();
	void SetRender(bool state);

};

#endif // !PLAYER