#pragma once

#include <iostream>

class Utils
{
public:
	static float dist(const sf::Vector2f p1, const sf::Vector2f p2)
	{
		float diffY = p1.y - p2.y;
		float diffX = p1.x - p2.x;
		return sqrt((diffY * diffY) + (diffX * diffX));
	}
	inline float static getRandomNumber(int min, int max)
	{
		return min + (std::rand() % (max - min + 1));
	}
	static float constrain(float value, float min, float max)
	{
		if (value <= min)
		{
			value = min;
		}

		if (value >= max)
		{
			value = max;
		}

		return value;
	}
};