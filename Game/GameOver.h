#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pipes.h"

class GameOver
{
public:
	GameOver();
	~GameOver();

	sf::Texture Game_Over, ScoreBoard;
	sf::Sprite Game_over_Sprite, ScoreBoardSprite;
	void PipeCollision(sf::RenderWindow &window, bool isGameOver);
	float ScoreSpeed = -9;
	float ScoreVelocity = 0;
	bool GameOverQueue = false;
};