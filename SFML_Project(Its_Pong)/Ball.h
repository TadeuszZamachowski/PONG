#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

class Ball
{
private:
	sf::Vector2f position;
	sf::CircleShape ball;

	float xVelocity = 0.4f;
	float yVelocity = 0.4f;
public:
	Ball(float xPos, float yPos);
	sf::FloatRect getPosition();
	sf::CircleShape getShape();
	float getXVelocity();
	float getYVelocity();
	void bounceFromWall(int windowHeight);
	void bounceFromPlayer(Player player);
	bool outOfBounds(int windowWidth, int windowHeight);
	void resetPosition(int windowWidth, int windowHeight);
	void updatePosition();
	//~Ball();
};

