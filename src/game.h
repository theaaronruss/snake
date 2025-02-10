#ifndef GAME_H
#define GAME_H

#include "game_window.h"
#include <deque>

struct Point {
	int x;
	int y;
};

enum class Direction {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake {
	private:
		std::deque<Point> body;
		Direction direction{ Direction::NONE };
	public:
		Snake();
		void changeDirection(Direction newDirection);
		const std::deque<Point>& getBody() const;
		void update();
		const Point getHead() const;
};

namespace Game {
	extern bool isGameOver;
	extern Snake snake;
	void update(int windowWidth, int windowHeight);
	void render(const GameWindow& window);
}

#endif
