#include "LifeBar.h"

LifeBar::LifeBar(Vector2 position, float offset)
{
	this->position = position;
	this->offset = offset;
}

LifeBar::~LifeBar()
{
	for(Figure* f : hearts)
		delete f;
}

void LifeBar::SetHearts(int hearts)
{
	for (Figure* f : this->hearts)
		delete f;
	this->hearts.clear();
	for (int i = 0; i < hearts; i++)
	{
		Figure* heart = new Figure();
		heart->LoadFigure("figures/Heart.gr");
		heart->SetScale(Vector2(0.8, 0.8));
		heart->SetPosition(position + Vector2(i * offset, 0));
		this->hearts.push_back(heart);
	}
}

int LifeBar::GetHearts()
{
	return hearts.size();
}

void LifeBar::AddHeart()
{
	Figure* heart = new Figure();
	heart->LoadFigure("figures/Heart.gr");
	heart->SetPosition(position + Vector2(hearts.size() * offset, 0));
	this->hearts.push_back(heart);
}

void LifeBar::RemoveHeart()
{
	if (hearts.size() > 0)
	{
		delete hearts.back();
		hearts.pop_back();
	}
}



