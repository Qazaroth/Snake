#include "Snake.h"

// Private

// Public
Snake::Snake(int s, sf::Window &window) : scale(s)
{
	this->x = window.getSize().x / 2;
	this->y = window.getSize().y / 2;
	//this->tails = new sf::Vector2f[this->total];
}

Snake::~Snake() 
{
	//delete[] this->tails;
}

void Snake::dir(int x, int y)
{
	this->xspeed = x;
	this->yspeed = y;
}

bool Snake::eat(sf::Vector2f foodPos)
{
	sf::Vector2f myPos(this->x, this->y);

	float d = Utils::dist(foodPos, myPos);

	if (d < scale)
	{
		this->total++;
		return true;
	}

	return false;
}

void Snake::death()
{
	for (int i = 0; i < this->tails.size(); i++)
	{
		sf::Vector2f pos = this->tails[i];
		sf::Vector2f myPos(this->x, this->y);
		float d = Utils::dist(myPos, pos);

		if (d < 1)
		{
			this->total = 0;
			this->tails.clear();
			this->tails.resize(0);
		}
	}
}

void Snake::update(sf::RenderWindow &window)
{
	this->tails.resize(this->total);

	if (this->total == this->tails.size() && this->tails.size() > 0)
	{
		for (int i = 0; i < this->tails.size() - 1; i++)
		{
			this->tails[i] = this->tails[i + 1];
		}
	}
	if (this->total > 0)
	{
		int ind = this->total - 1;
		if (ind < 0) ind = 0;
		this->tails[ind] = sf::Vector2f(this->x, this->y);
	}

	int width = window.getSize().x;
	int height = window.getSize().y;

	this->x = this->x + this->xspeed * scale;
	this->y = this->y + this->yspeed * scale;

	this->x = Utils::constrain(this->x, 0, width - scale);
	this->y = Utils::constrain(this->y, 0, height - scale);
	//this->x = Utils::constrain(this->x, -(width/2), width/2 - scale);
	//this->y = Utils::constrain(this->y, -(height/2), (height/2 - scale));
}

void Snake::show(sf::RenderWindow &window) 
{
	sf::Vector2f size = sf::Vector2f(this->scale, this->scale);

	if (this->total > 0)
	{
		for (int i = 0; i < this->tails.size(); i++)
		{
			sf::RectangleShape t(size);
			t.setOutlineThickness(1);
			t.setOutlineColor(sf::Color::Black);
			t.setPosition(this->tails[i].x, this->tails[i].y);
			t.setFillColor(sf::Color::White);

			window.draw(t);
		}
	}

	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	rect.setPosition(sf::Vector2f(this->x, this->y));
	rect.setSize(size);
	rect.setFillColor(sf::Color::White);

	window.draw(rect);
}