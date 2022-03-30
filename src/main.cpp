#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Utils.h"
#include "FPSTimer.h"

#define FRAMECAP 15

std::string TITLE = "Snake in C++";
sf::Uint32 styleFlag = sf::Style::Default;

FPSTimer timer;
float timerCounter = 0;
unsigned int frames = 0;

int scale = 20;

sf::Vector2f food;

void pickLocation(int width, int height)
{
	int cols = floor(width / scale);
	int rows = floor(height / scale);

	food.x = floor(Utils::getRandomNumber(0, cols/2));//floor(Utils::getRandomNumber(-(cols / 2), (cols / 2)));
	food.y = floor(Utils::getRandomNumber(0, rows/2));//floor(Utils::getRandomNumber(-(rows / 2), (rows / 2)));
	food.x *= scale;
	food.y *= scale;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), TITLE, styleFlag);
	window.setFramerateLimit(FRAMECAP);

	Snake s(scale, window);

	sf::Vector2u size = window.getSize();
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(size.x, size.y));

	//window.setView(view);

	int width = window.getSize().x;
	int height = window.getSize().y;
	
	pickLocation(width, height);

	while (window.isOpen())
	{
		sf::Event windowEvent;
		sf::RectangleShape foodRect(sf::Vector2f(scale, scale));

		width = window.getSize().x;
		height = window.getSize().y;

		window.clear(sf::Color(51, 51, 51, 255));

		if (s.eat(food))
		{
			pickLocation(width, height);
		}

		s.death();
		s.update(window);
		s.show(window);
		foodRect.setFillColor(sf::Color(255, 0, 100, 255));
		foodRect.setPosition(food);
		window.draw(foodRect);
		window.display();

		while (window.pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case sf::Event::KeyPressed:
			{
				auto keyCode = windowEvent.key.code;
				if (keyCode == sf::Keyboard::Up)
				{
					s.dir(0, -1);
				}
				else if (keyCode == sf::Keyboard::Down)
				{
					s.dir(0, 1);
				}
				else if (keyCode == sf::Keyboard::Right)
				{
					s.dir(1, 0);
				}
				else if (keyCode == sf::Keyboard::Left)
				{
					s.dir(-1, 0);
				}
				break;
			}
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		frames++;
		if (timer.elapsed() - timerCounter > 1.0f)
		{
			timerCounter += 1.0f;
			printf("%d FPS\n", frames);
			frames = 0;
		}
	}

	return 0;
}