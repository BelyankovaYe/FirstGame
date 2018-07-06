#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pipes.h"


int main()
{
	sf::Vector2f velocity(sf::Vector2f(0, 0));
	sf::Vector2u windowSize(800, 700);
	sf::Vector2i NumberPosition(380, 40);
	const float gravity = 0.3;
	int groundHeight = 640;
	int AngleIncrease = -30;
	int AngleDownfall = 1;
	float moveSpeed = 5, jumpSpeed = 2.5;
	float Angle = 0;

	bool Once = false;
	bool OnePerPoint = false;
	bool CollisionHit = false;
	bool GameStart = false;
	bool GameOverFix = false;
	bool GameOverFix1 = false;
	bool SecondHitPrevent = true;
	int FlappyPoints = 0;
	Pipes pipe1(800, 378, 0, 830);
	Pipes pipe2(800, 378, 400, 830);
	GameOver End;




	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "FlappyBird");
	sf::Texture Flappy, BackGround;
	sf::Sprite FlappyBird, BackGroundSprite;
	if (!Flappy.loadFromFile("images/FlappyBird.png", sf::IntRect(0, 490, 25, 25)))
	{
	}
	if (!BackGround.loadFromFile("images/FlappyBird.png", sf::IntRect(146, 0, 144, 256)))
	{
	}
	BackGroundSprite.setTexture(BackGround);
	BackGroundSprite.setScale(5.6, 3);
	FlappyBird.setTexture(Flappy);
	FlappyBird.setPosition(200, 300);
	FlappyBird.setScale(3, 3);
	window.setFramerateLimit(120);
	std::cout << FlappyPoints << std::endl;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		while (!GameStart)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				GameStart = true;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(BackGroundSprite);
			window.draw(FlappyBird);
			window.display();

		}
		// the bird flies
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x = moveSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x = -moveSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!Once)
			{

				Angle = AngleIncrease;
				if (!CollisionHit)
				{
					velocity.y = 0;
				}
				velocity.y += -jumpSpeed * 3;

				Once = true;
			}
		}
		else
		{
			velocity.x = 0;
			Once = false;
		}
		FlappyBird.move(velocity.x, velocity.y);



		FlappyBird.setRotation(Angle);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			return main();
		}
		//hit the pipe
		if ((pipe1.OverlapTest(FlappyBird.getPosition().x, FlappyBird.getPosition().y)) ||
			(pipe1.OverlapTest(FlappyBird.getPosition().x, FlappyBird.getPosition().y)) ||
			(pipe2.OverlapTest(FlappyBird.getPosition().x, FlappyBird.getPosition().y)) ||
			(pipe2.OverlapTest(FlappyBird.getPosition().x, FlappyBird.getPosition().y)))
		{
			if (GameOverFix)
			{
				NumberPosition.y += -9;
				if (NumberPosition.y <= 300)
				{
					NumberPosition.y = 300;
				}
			}
			else
			{
				pipe1.Speed = 0;
				pipe2.Speed = 0;
				moveSpeed = 0;
				jumpSpeed = 0;
				NumberPosition.x = 545;
				NumberPosition.y = 870;
				AngleDownfall = 3;
				AngleIncrease = 60;
				SecondHitPrevent = false;
				CollisionHit = true;

			}
		}
		if (pipe1.Points(FlappyBird.getPosition().x) || pipe2.Points(FlappyBird.getPosition().x))
		{
			if (!OnePerPoint)
			{

				FlappyPoints++;
				std::cout << FlappyPoints << std::endl;
				OnePerPoint = true;
			}
		}
		else
			OnePerPoint = false;

		// the ground fall
		if (FlappyBird.getPosition().y + FlappyBird.getScale().y < groundHeight || velocity.y < 0)
		{
			velocity.y += gravity;
		}
		else
		{
			if (SecondHitPrevent)
			{
				if (GameOverFix1)
				{
					NumberPosition.y += -9;
					if (NumberPosition.y <= 300)
					{
						NumberPosition.y = 300;
					}
				}
				else
				{
					FlappyBird.setPosition(FlappyBird.getPosition().x, groundHeight - FlappyBird.getScale().y);
					velocity.y = 0;
					CollisionHit = true;
					pipe1.Speed = 0;
					pipe2.Speed = 0;
					moveSpeed = 0;
					jumpSpeed = 0;
					NumberPosition.x = 545;
					NumberPosition.y = 870;
					AngleIncrease = 60;
					AngleDownfall = 3;
				}
			}
			else
			{
				FlappyBird.setPosition(FlappyBird.getPosition().x, groundHeight - FlappyBird.getScale().y);
				velocity.y = 0;
			}
		}
		if (Angle < 60)
			Angle += AngleDownfall;
		window.clear();
		window.draw(BackGroundSprite);
		pipe1.draw(window);
		pipe2.draw(window);
		window.draw(FlappyBird);
		End.PipeCollision(window, CollisionHit);
		window.display();
	}

	return 0;
}
