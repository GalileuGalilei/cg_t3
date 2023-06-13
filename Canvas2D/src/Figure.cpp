#include "Figure.h"
#include <cmath>

Figure::Figure()
{

}

Figure::~Figure()
{
	for (ConcavePolygon* polygon : polygons)
	{
		delete polygon;
	}
}

void Figure::CalculatePivot()
{
	Vector2 sum = Vector2(0, 0);
	int count = 0;
	for (ConcavePolygon* polygon : polygons)
	{
		sum += polygon->GetCenter();
		count++;
	}
	pivot = sum / count;
}

void Figure::SetPosition(Vector2 position)
{
	Vector2 newPivot = position;

	for (ConcavePolygon* polygon : polygons)
	{
		Vector2 translation = newPivot - pivot;
		polygon->Translate(translation);
	}

	pivot = position;
}

void Figure::SetRotation(float angle)
{
	for (ConcavePolygon* polygon : polygons)
	{
		polygon->Rotate(angle - this->angle, pivot);
	}
	this->angle = angle;
}

void Figure::Rotate(float angle)
{
	for (ConcavePolygon* polygon : polygons)
	{
		polygon->Rotate(angle, pivot);
	}
}

void Figure::Rotate(float angle, Vector2 pivot)
{
	for (ConcavePolygon* polygon : polygons)
	{
		polygon->Rotate(angle, pivot);
	}
}

void Figure::SetScale(Vector2 scale)
{
	for (ConcavePolygon* polygon : polygons)
	{
		polygon->Scale(scale, pivot);
	}
}

void Figure::LoadFigure(const char path[])
{
	FILE* f;
	fopen_s(&f, path, "rb");

	if (f == NULL)
	{
		printf("Error loading figure file\n");
		return;
	}

	while (!feof(f))
	{
		PolygonData data;
		fread(&data, sizeof(PolygonData), 1, f);

		if (data.tam < 1)
		{
			break;
		}

		std::vector<float> x(data.tam);
		std::vector<float> y(data.tam);

		fread(x.data(), sizeof(float), data.tam, f);
		fread(y.data(), sizeof(float), data.tam, f);

		ConcavePolygon* polygon = new ConcavePolygon(std::vector<Vector2>());
		polygon->LoadData(data, x, y);
		polygon->Triangulate();
		polygons.push_back(polygon);
	}

	fclose(f);
	CalculatePivot();
}

void Figure::AlignWith(Vector2 target)
{
	Vector2 direction = target - pivot;
	direction.normalize();
	float cossine = direction.dot(Vector2(0, 1));
	float angle = -std::acos(cossine);
	if (direction.x < 0)
	{
		angle = 3.141529 * 2 - angle;
	}

	this->SetRotation(angle);
}

void Figure::SetRender(bool state)
{
	for (ConcavePolygon* polygon : polygons)
	{
		polygon->SetRender(state);
	}
}