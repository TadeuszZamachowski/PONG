
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Ball.h"

#define WIDTH 1024
#define HEIGHT 768

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 100


int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PONG");

	Player player1(10, (HEIGHT - 100) / 2);
	Player player2(993, (HEIGHT - 100) / 2);

	Ball ball((WIDTH / 2), (HEIGHT / 2));

	sf::Text p1Hud, p2Hud, gameOver;
	sf::Font font;
	font.loadFromFile("ARCADECLASSIC.TTF");

	p1Hud.setFont(font);
	p1Hud.setCharacterSize(70);
	p1Hud.setFillColor(sf::Color::White);
	p1Hud.setPosition(sf::Vector2f(30, 0));

	p2Hud.setFont(font);
	p2Hud.setCharacterSize(70);
	p2Hud.setFillColor(sf::Color::White);
	p2Hud.setPosition(sf::Vector2f(WIDTH - p2Hud.getCharacterSize(), 0));

	gameOver.setFont(font);
	gameOver.setCharacterSize(70);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setPosition(sf::Vector2f((WIDTH - gameOver.getCharacterSize()) / 4 , 0));


	bool resumeGame = false;
	bool pointScored = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			resumeGame = true;
		}

		if (resumeGame)
		{
			ball.bounceFromWall(HEIGHT);
			ball.bounceFromPlayer(player1);
			ball.bounceFromPlayer(player2);
			if (ball.outOfBounds(WIDTH, HEIGHT))
			{
				if (ball.getPosition().left > WIDTH)
				{
					player1.points += 1;
				}
				else
				{
					player2.points += 1;
				}
				ball.resetPosition(WIDTH, HEIGHT);
				resumeGame = false;
			}
			ball.updatePosition();	
		}

		player1.handleInput(false);
		player1.checkBounds(HEIGHT);

		player2.handleInput(true);
		player2.checkBounds(HEIGHT);

		std::string p1Points = std::to_string(player1.points);
		std::string p2Points = std::to_string(player2.points);
		p1Hud.setString(p1Points);
		p2Hud.setString(p2Points);

		if (player1.points >= 2)
		{
			resumeGame = false;
			std::stringstream gameOverText;
			gameOverText << "            GAME   OVER" << '\n' << "       PLAYER   1   WINS" << '\n' << "PRESS SPACE TO RESTART";
			gameOver.setString(gameOverText.str());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				player1.points = 0;
				player2.points = 0;
				resumeGame = true;
			}
		}
		else if (player2.points >= 2)
		{
			resumeGame = false;
			std::stringstream gameOverText;
			gameOverText << "GAME   OVER" << '\n' << "PLAYER   2   WINS" << '\n' << "PRESS SPACE TO RESTART";
			gameOver.setString(gameOverText.str());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				player1.points = 0;
				player2.points = 0;
				resumeGame = true;
			}
		}

		window.clear();
		window.draw(player1.getShape());
		window.draw(player2.getShape());
		if (player1.points < 2 || player2.points < 2)
		{
			window.draw(ball.getShape());
		}
		else
		{
		}
		window.draw(p1Hud);
		window.draw(p2Hud);
		window.draw(gameOver);
		window.display();

	}

	return 0;
}
