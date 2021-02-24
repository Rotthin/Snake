#include "snake.hpp"
#include <iostream>

Snake::Snake() {
	dir = Direction::LEFT;
	size = 3;
	tickRate = 200000000;

	tail[0].x = 10;
	tail[0].y = 10;

	shape.setSize(sf::Vector2f(UNIT_SIZE-2, UNIT_SIZE-2));
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2);

	updateTail();
}

void Snake::updateTail() {
	for (unsigned int i = size; i>0; i--) {
		tail[i].x = tail[i-1].x;
		tail[i].y = tail[i-1].y;
	}
}

void Snake::eat() {
	size++;
	if (tickRate > 75000000) {
		tickRate -= 5000000;
	}
}

void Snake::tick() {
	changeDir(queuedDir);
	updateTail();

	switch (dir) {
	case Direction::UP:
		tail[0].y--;
		break;
	
	case Direction::DOWN:
		tail[0].y++;
		break;

	case Direction::LEFT:
		tail[0].x--;
		break;
	
	case Direction::RIGHT:
		tail[0].x++;
		break;
	}

	std::cout << "\ntick\n";
	std::cout << "head: x:" << tail[0].x << ",  y:" << tail[0].y << "\n";
	std::cout << "dir: " << (int)dir << "\n";
	std::cout << "size: " << size << "\n";
	std::cout << "tick rate: " << tickRate << "\n";
}

void Snake::draw(sf::RenderWindow& p_window) {
	shape.setFillColor(sf::Color::Green);
	for (unsigned int i = 0; i<=size; i++) {
		shape.setFillColor(sf::Color(0, 100+(155*((float)i/(float)size)), 0));
		shape.setPosition(tail[i].x*UNIT_SIZE+1, tail[i].y*UNIT_SIZE+1);
		p_window.draw(shape);
	}
}

void Snake::changeDir(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Left: queuedDir = Direction::LEFT; break;
	case sf::Keyboard::Right: queuedDir = Direction::RIGHT; break;
	case sf::Keyboard::Up: queuedDir = Direction::UP; break;
	case sf::Keyboard::Down: queuedDir = Direction::DOWN; break;
	}
}

void Snake::changeDir(Direction newDir) {
	switch (newDir) {
	case Direction::UP:
		if (dir != Direction::DOWN || size==0)
			dir = newDir;
		break;

	case Direction::DOWN:
		if (dir != Direction::UP || size==0)
			dir = newDir;
		break;

	case Direction::LEFT:
		if (dir != Direction::RIGHT || size==0)
			dir = newDir;
		break;

	case Direction::RIGHT:
		if (dir != Direction::LEFT || size==0)
			dir = newDir;
		break;
	}
}

bool Snake::isColliding() {
	if (tail[0].x >= GRID_SIZE || tail[0].x < 0 || tail[0].y < 0 || tail[0].y >= GRID_SIZE) {
		return true;
	}

	int x = tail[0].x;
	int y = tail[0].y;
	for (unsigned int i = 1; i<=size; i++) {
		if (x == tail[i].x && y == tail[i].y) {
			return true;
		}
	}

	return false;
}