#include "game.h"
#include "game_window.h"
#include <algorithm>
#include <deque>
#include <random>

Snake::Snake() {
	body.push_front(Point{ 16, 12 }); // head
	body.push_back(Point{ 16, 11 });
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

std::deque<Point>& Snake::getBody() {
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

const Point Snake::getTail() const {
	return body[body.size() - 1];
}

bool Game::isGameOver{ false };

Snake Game::snake{};

std::default_random_engine Game::generator{};

Point Game::food{};

int Game::points{ 0 };

void Game::update(int windowWidth, int windowHeight) {
	snake.update();
	std::deque<Point> snakeBody = snake.getBody();
	const Point snakeHead = snake.getHead();
	Point oldTail = snake.getTail();
	if (snakeHead.x < 0 || snakeHead.x >= windowWidth
		|| snakeHead.y < 0 || snakeHead.y >= windowHeight) {
		isGameOver = true;
	}
	if (snakeHead.x == food.x && snakeHead.y == food.y) {
		points++;
		getNewFoodLocation(windowWidth, windowHeight);
		snake.getBody().push_back(oldTail);
	}
	auto it = std::find_if(snakeBody.begin() + 1, snakeBody.end(), [&snakeHead](const Point p) {
		return p.x == snakeHead.x && p.y == snakeHead.y;
	});
	if (it != snakeBody.end()) {
		isGameOver = true;
	}
}

void Game::render(const GameWindow &window) {
	for (Point pixel : snake.getBody()) {
		window.turnPixelOn(pixel.x, pixel.y);
	}
	window.turnPixelOn(food.x, food.y);
}

void Game::getNewFoodLocation(int windowWidth, int windowHeight) {
	std::uniform_int_distribution<int> distributionX(0, windowWidth - 1);
	std::uniform_int_distribution<int> distributionY(0, windowHeight - 1);
	int x = distributionX(generator);
	int y = distributionY(generator);
	food = Point{ x, y };
}
