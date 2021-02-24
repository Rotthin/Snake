#pragma once

#include "libs.hpp"
#include <list>
#include "point.hpp"

class Snake {
public:
	Snake();
	enum class Direction { UP, DOWN, LEFT, RIGHT };
private:
	sf::RectangleShape shape;
	Direction dir;
	Direction queuedDir;
private:
	void updateTail();
public:
	unsigned int tickRate;
	Point tail[GRID_SIZE*GRID_SIZE];
	unsigned int size;
public:
	void tick();
	void draw(sf::RenderWindow& p_window);
	void changeDir(Direction newDir);
	void changeDir(sf::Keyboard::Key e);
	void eat();
	bool isColliding();
};