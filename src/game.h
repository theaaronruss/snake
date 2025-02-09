#ifndef GAME_H
#define GAME_H

#include "game_window.h"
//#include "point.h"
#include <deque>

struct Point {
	int x;
	int y;
};

class Snake {
	private:
		std::deque<Point> body;
	public:
		Snake();
		const std::deque<Point>& getBody() const;
};

namespace Game {
	extern Snake snake;
	void render(const GameWindow& window);
}

#endif
