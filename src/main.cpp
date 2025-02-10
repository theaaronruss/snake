#include "SDL3/SDL.h"
#include "game.h"
#include "game_window.h"
#include <stdexcept>

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	try {
		GameWindow window;
		bool running{ true };
		const long updateInterval{ 1000 / 15 };
		long lastUpdateTime{ 0 };
		while (running) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_QUIT) {
					running = false;
				} else if (event.type == SDL_EVENT_KEY_DOWN) {
					if (event.key.key == SDLK_UP) {
						Game::snake.changeDirection(Direction::UP);
					} else if (event.key.key == SDLK_DOWN) {
						Game::snake.changeDirection(Direction::DOWN);
					} else if (event.key.key == SDLK_LEFT) {
						Game::snake.changeDirection(Direction::LEFT);
					} else if (event.key.key == SDLK_RIGHT) {
						Game::snake.changeDirection(Direction::RIGHT);
					}
				}
			}
			long now = SDL_GetTicks();
			window.clear();
			if (now - lastUpdateTime > updateInterval) {
				Game::update();
				lastUpdateTime = now;
			}
			Game::render(window);
			window.update();
		}
	} catch (const GameWindowCreationException& e) {
		SDL_Log("%s", e.what());
		SDL_Log("SDL error: %s", SDL_GetError());
	}
	SDL_Quit();
	return 0;
}
