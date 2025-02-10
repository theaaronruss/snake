#include "game.h"
#include "game_window.h"
#include <deque>

Snake::Snake() {
	body.push_front(Point{ 16, 12 }); // head
	body.push_back(Point{ 16, 11 });
	body.push_back(Point{ 16, 10 });
}

void Snake::changeDirection(Direction newDirection) {
	direction = newDirection;
}

const std::deque<Point>& Snake::getBody() const {
	return body;
}

void Snake::update() {
	Point currentHead = body.at(0);
	if (direction == Direction::UP) {
		currentHead.y--;
		body.push_front(currentHead);
	} else if (direction == Direction::DOWN) {
		currentHead.y++;
		body.push_front(currentHead);
	} else if (direction == Direction::LEFT) {
		currentHead.x--;
		body.push_front(currentHead);
	} else if (direction == Direction::RIGHT) {
		currentHead.x++;
		body.push_front(currentHead);
	}
	body.pop_back();
}

Snake Game::snake{};

void Game::update() {
	snake.update();
}

void Game::render(const GameWindow &window) {
	for (Point pixel : snake.getBody()) {
		window.turnPixelOn(pixel.x, pixel.y);
	}
}
