#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player
{
private:
	sf::Vector2f position;
	sf::RectangleShape player;
	float velocity = 0.3f;
public:
	int points;
	Player(float xPos, float yPos);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	void handleInput(bool arrows);
	void checkBounds(int windowHeight);
	void moveUp();
	void moveDown();
	void updatePosition();
	//~Player();
};

