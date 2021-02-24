#include "libs.hpp"
#include <iostream>
#include <chrono>
#include <list>
#include "snake.hpp"
#include "food.hpp"
#include "main.hpp"
#include "saveSystem.hpp"

std::chrono::high_resolution_clock::time_point lastTick;

sf::Font font;

sf::Text scoreText;
sf::Text hsText;
sf::RectangleShape tile;

Snake snake;
Food food;

int main() {
	if (!init()) { return 1; }

	sf::RenderWindow window(sf::VideoMode(640, 700), "Snake by Rotthin", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);

	sf::Image icon;
	icon.loadFromFile("res/textures/icon.png");
	window.setIcon(512, 512, icon.getPixelsPtr());

	while (window.isOpen()) {
		startFrame(window);
		update(window);
		render(window);
	}
}

bool init() {
	srand(time(0));
		
	if (!font.loadFromFile("res/fonts/fixedsys.ttf"))
		return false;

	tile.setSize(sf::Vector2f(UNIT_SIZE, UNIT_SIZE));
	tile.setOutlineColor(sf::Color(80, 80, 80));
	tile.setOutlineThickness(1);

	scoreText.setFont(font);
	scoreText.setCharacterSize(32);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(3);

	hsText.setFont(font);
	hsText.setCharacterSize(32);
	hsText.setOutlineColor(sf::Color::Black);
	hsText.setOutlineThickness(3);
	updateScore();

	food.spawn();

	return true;
} 

void startFrame(sf::RenderWindow& p_window) {
	pollEvents(p_window);
	p_window.clear(sf::Color::White);
}

void pollEvents(sf::RenderWindow& p_window) {
	sf::Event e;
	while (p_window.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			p_window.close();
			break;
		case sf::Event::KeyPressed:
			snake.changeDir(e.key.code);
			break;
		}
	}
}

void update(sf::RenderWindow& p_window) {
	if ((std::chrono::high_resolution_clock::now()-lastTick).count() > snake.tickRate) {
		tick();
	}
}

void render(sf::RenderWindow& p_window) {
	drawGrid(p_window);
	food.draw(p_window);
	snake.draw(p_window);

	p_window.draw(scoreText);
	p_window.draw(hsText);

	p_window.display();
}

void tick() {
	if (food.pos.isOverlapping(snake.tail[0])) {
		snake.eat();
		food.spawn();

		updateScore();
	}

	snake.tick();

	if (snake.isColliding())
		gameOver();

	lastTick = std::chrono::high_resolution_clock::now();
}

void updateScore() {
	int hs = rott::saving::loadInt("hs.save");

	if (snake.size > hs) {
		hs = snake.size;
		rott::saving::saveInt("hs.save", hs);
	}

	scoreText.setString("Length: " + std::to_string(snake.size));
	scoreText.setPosition(20, 640);

	hsText.setString("HS: " + std::to_string(hs));
	hsText.setPosition((640-hsText.getLocalBounds().width-20), 640);
}

void gameOver() {
	snake = Snake();
	food.spawn();
	updateScore();
}

void drawGrid(sf::RenderWindow& p_window) {
	for (int x = 0; x<GRID_SIZE; x++) {
		for (int y = 0; y<GRID_SIZE; y++) {
			tile.setPosition(sf::Vector2f(x*UNIT_SIZE, y*UNIT_SIZE));

			p_window.draw(tile);
		}
	}
}
