#include "SDL3/SDL.h"
#include "game_window.h"
#include <stdexcept>

int main() {
    SDL_Log("Initializing SDL");
    SDL_Init(SDL_INIT_VIDEO);
    try {
        GameWindow window;
        bool running { true };
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    running = false;
                }
            }
            window.clear();
            window.update();
        }
    } catch (const GameWindowException& e) {
        SDL_Log("%s", e.what());
        SDL_Log("SDL error: %s", SDL_GetError());
    }
    SDL_Log("Quitting SDL");
    SDL_Quit();
    return 0;
}
