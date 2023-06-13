#ifndef FIGURE
#define FIGURE
#include "ConcavePolygon.h"
#include <vector>

class Figure
{
private:
	Vector2 pivot;
	float angle = 0; //angulo 0 aponta para cima
	void CalculatePivot();

public:
	std::vector<ConcavePolygon*> polygons;
	Figure();
	~Figure();

	void SetPosition(Vector2 position);
	void SetRotation(float angle);
	void SetScale(Vector2 scale);
	void Rotate(float angle);
	void Rotate(float angle, Vector2 pivot);

	void LoadFigure(const char path[]);
	void AlignWith(Vector2 target);
	void SetRender(bool state);
};

#endif // !FIGURE