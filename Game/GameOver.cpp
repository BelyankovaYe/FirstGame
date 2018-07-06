#include "GameOver.h"
#include "Pipes.h"
#include <SFML/Graphics.hpp>
#include <iostream>



GameOver::GameOver()
{
	if (!Game_Over.loadFromFile("images/FlappyBird.png", sf::IntRect(395, 59, 100, 21)))
	{
	}
	Game_over_Sprite.setTexture(Game_Over);
	Game_over_Sprite.setScale(3, 3);
	Game_over_Sprite.setPosition(250, 710);
}


GameOver::~GameOver()
{
}

void GameOver::PipeCollision(sf::RenderWindow &window, bool isGameOver)
{
	if (isGameOver)
	{
		if (Game_over_Sprite.getPosition().y <= 300)
		{
			ScoreSpeed = 0;
			ScoreVelocity = 0;
		}

		Game_over_Sprite.move(0, ScoreSpeed);
		window.draw(Game_over_Sprite);
	}
}
