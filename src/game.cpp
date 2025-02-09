#include "game.h"
#include "game_window.h"

Snake Game::snake;

void Game::render(const GameWindow& window) {
	window.turnPixelOn(snake.getHeadX(), snake.getHeadY());
}

int Snake::getHeadX() {
	return headX;
}

int Snake::getHeadY() {
	return headY;
}
