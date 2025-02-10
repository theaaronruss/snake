#include "game.h"
#include "game_window.h"
#include <deque>

Snake::Snake() {
	body.push_front(Point{ 16, 12 }); // head
	body.push_back(Point{ 16, 11 });
	body.push_back(Point{ 16, 10 });
}

void Snake::changeDirection(Direction newDirection) {
	// prevent player from choosing a direction that will result in immediately losing
	if (direction == Direction::UP && newDirection == Direction::DOWN
		|| direction == Direction::DOWN && newDirection == Direction::UP
		|| direction == Direction::LEFT && newDirection== Direction::RIGHT
		|| direction == Direction::RIGHT && newDirection == Direction::LEFT) {
		return;
	}
	if (frozen) {
		frozen = false;
	}
	direction = newDirection;
}

const std::deque<Point>& Snake::getBody() const {
	return body;
}

void Snake::update() {
	if (frozen) {
		return;
	}
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

const Point Snake::getHead() const {
	return body[0];
}

bool Game::isGameOver{ false };

Snake Game::snake{};

void Game::update(int windowWidth, int windowHeight) {
	snake.update();
	Point snakeHead = snake.getHead();
	if (snakeHead.x < 0 || snakeHead.x >= windowWidth
		|| snakeHead.y < 0 || snakeHead.y >= windowHeight) {
		isGameOver = true;
	}
}

void Game::render(const GameWindow &window) {
	for (Point pixel : snake.getBody()) {
		window.turnPixelOn(pixel.x, pixel.y);
	}
}
