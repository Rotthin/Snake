#pragma once

#include "point.hpp"
#include "libs.hpp"

class Food {
public:
	Point pos;
	sf::RectangleShape shape;
public:
	Food();
	void spawn();
	void draw(sf::RenderWindow& p_window);
};

