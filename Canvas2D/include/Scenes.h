#ifndef SCENE
#define SCENE

#include "Botao.h"
#include "GameEvents.h"
#include <string>
#include <functional>

class GameOverScene : public IRenderable
{
	private:
	Button* botao;
	int score = 0;
	bool isGameOver = true;

	public:
		GameOverScene(std::function<void()> RestartFunction, int score)
		{
			botao = new Button(Vector2(270, 210), Vector2(100, 30), Colors::red, "RESTART", RestartFunction);
			this->score = score;
		}

		~GameOverScene()
		{
			delete botao;
		}

		void OnRender(OnRenderEvent* args) override
		{
			CV::color(1, 0, 0);
			CV::text(270, 310, "GAME OVER");

			CV::color(1, 1, 1);
			std::string scoreText = "Score: " + std::to_string(score);
			CV::text(270, 280, scoreText.c_str());
		}
};



#endif // !SCENE
