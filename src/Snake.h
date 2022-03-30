#pragma once

#include <SFML/Graphics.hpp>

#include <list>

#include "Utils.h"

class Snake
{
private:
	int x = 0;
	int y = 0;
	int xspeed = 1;
	int yspeed = 0;

	std::vector<sf::Vector2f> tails;

	int total = 0;

	int scale = 1;

	sf::RectangleShape rect;
public:
	Snake(int scale, sf::Window &window);
	~Snake();

	bool eat(sf::Vector2f foodPos);

	void death();

	void dir(int x, int y);
	void update(sf::RenderWindow &window);
	void show(sf::RenderWindow &window);
};

