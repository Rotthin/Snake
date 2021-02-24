#include "food.hpp"
#include "libs.hpp"

Food::Food() {
	shape.setSize(sf::Vector2f(UNIT_SIZE-2, UNIT_SIZE-2));
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2);
}

void Food::spawn() {
	pos.x = rand() % GRID_SIZE;
	pos.y = rand() % GRID_SIZE;
}

void Food::draw(sf::RenderWindow& p_window){
	shape.setPosition(pos.x*UNIT_SIZE+1, pos.y*UNIT_SIZE+1);
	p_window.draw(shape);
}