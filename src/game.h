#ifndef GAME_H
#define GAME_H

#include "game_window.h"

class Snake {
	private:
		int headX{ 16 };
		int headY{ 12 };
	public:
		int getHeadX();
		int getHeadY();
};

namespace Game {
	extern Snake snake;
	void render(const GameWindow& window);
}

#endif
