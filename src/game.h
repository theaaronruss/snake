#ifndef GAME_H
#define GAME_H

#include "game_window.h"
#include <deque>
#include <random>

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
		bool frozen{ true };
		std::deque<Point> body;
		Direction direction{ Direction::DOWN };
	public:
		Snake();
		void changeDirection(Direction newDirection);
		std::deque<Point>& getBody();
		void update();
		const Point getHead() const;
		const Point getTail() const;
};

namespace Game {
	extern bool isGameOver;
	extern Snake snake;
	extern std::default_random_engine generator;
	extern Point food;
	extern int points;
	void update(int windowWidth, int windowHeight);
	void render(const GameWindow& window);
	void getNewFoodLocation(int windowWidth, int windowHeight);
}

#endif
