#ifndef LIFE_BAR
#define LIFE_BAR
#include "GameEvents.h"
#include "Figure.h"

class LifeBar
{
private:
	std::list<Figure*> hearts;
	Vector2 position;
	float offset;

public:
	LifeBar(Vector2 position, float offset);
	~LifeBar();
	void SetHearts(int hearts);
	void AddHeart();
	void RemoveHeart();
	int GetHearts();

};

#endif // !LIFE_BAR