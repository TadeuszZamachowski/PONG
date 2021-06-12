#include "Ball.h"



Ball::Ball(float xPos, float yPos)
{
	position.x = xPos;
	position.y = yPos;

	ball.setRadius(8.f);
	ball.setPosition(position);
}

sf::FloatRect Ball::getPosition()
{
	return ball.getGlobalBounds();
}

sf::CircleShape Ball::getShape()
{
	return ball;
}

float Ball::getXVelocity()
{
	return xVelocity;
}

float Ball::getYVelocity()
{
	return yVelocity;
}


void Ball::bounceFromWall(int windowHeight)
{
	if (position.y > windowHeight - 2*ball.getRadius() || position.y < 0)
	{
		yVelocity = -yVelocity;
	}
}

void Ball::bounceFromPlayer(Player player)
{
	if (this->getPosition().intersects(player.getPosition()))
	{
		position.x -= xVelocity * 10;
		xVelocity = -xVelocity;
	}
}

bool Ball::outOfBounds(int windowWidth, int windowHeight)
{
	if (position.x > windowWidth || position.x < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Ball::resetPosition(int windowWidth, int windowHeight)
{
	if (position.x > windowWidth || position.x < 0)
	{
		position.x = windowWidth / 2;
		position.y = windowHeight / 2;
	}
}

void Ball::updatePosition()
{
	position.x += xVelocity;
	position.y += yVelocity;

	ball.setPosition(position);
}


