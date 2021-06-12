#include "Player.h"



Player::Player(float xPos, float yPos)
{
	position.x = xPos;
	position.y = yPos;
	points = 0;

	player.setSize(sf::Vector2f(20, 100));
	player.setPosition(position);
}

sf::FloatRect Player::getPosition()
{
	return player.getGlobalBounds();
}

sf::RectangleShape Player::getShape()
{
	return player;
}

void Player::moveUp()
{
	position.y -= velocity;
}

void Player::moveDown()
{
	position.y += velocity;
}

void Player::updatePosition()
{
	player.setPosition(position);
}

void Player::handleInput(bool arrows)
{
	if (arrows)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->moveDown();
			this->updatePosition();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->moveUp();
			this->updatePosition();
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->moveDown();
			this->updatePosition();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->moveUp();
			this->updatePosition();
		}
	}
}

void Player::checkBounds(int windowHeight)
{
	if (this->getPosition().top > windowHeight)
	{
		//position.y = 0;
		position.y = -this->getPosition().height;
	}
	else if (this->getPosition().top + this->getPosition().height < 0)
	{
		position.y = windowHeight;
	}
}



