#include "game.h"
#include "game_window.h"
#include <deque>

Snake::Snake() {
	body.push_front(Point{ 16, 12 }); // head
	body.push_back(Point{ 16, 11 });
	body.push_back(Point{ 16, 10 });
}

const std::deque<Point>& Snake::getBody() const {
	return body;
}

Snake Game::snake{};

void Game::render(const GameWindow& window) {
	for (Point pixel : snake.getBody()) {
		window.turnPixelOn(pixel.x, pixel.y);
	}
}
