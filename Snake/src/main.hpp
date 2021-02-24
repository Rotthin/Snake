#pragma once

#include "libs.hpp"

void updateScore();
void gameOver();
void drawGrid(sf::RenderWindow& p_window);
bool init();
void tick();
void update(sf::RenderWindow& p_window);
void pollEvents(sf::RenderWindow& p_window);
void startFrame(sf::RenderWindow& p_window);
void render(sf::RenderWindow& p_window);