#ifndef GAME_H
#define GAME_H

#include "game_window.h"
#include <deque>

struct Point {
	int x;
	int y;
};

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake {
	private:
		std::deque<Point> body;
		Direction direction;
	public:
		Snake();
		void changeDirection(Direction newDirection);
		const std::deque<Point>& getBody() const;
		void update();
};

namespace Game {
	extern Snake snake;
	void update();
	void render(const GameWindow& window);
}

#endif
