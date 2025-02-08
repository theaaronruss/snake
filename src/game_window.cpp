#include "SDL3/SDL.h"
#include "game_window.h"
#include <stdexcept>

GameWindow::GameWindow() {
    SDL_Log("Creating game window and renderer");
    bool success = SDL_CreateWindowAndRenderer(title, width, height, 0, &window, &renderer);
    if (!success) {
        throw GameWindowException("Failed to create game window and renderer");
    }
}

GameWindow::~GameWindow() {
    SDL_Log("Destroying game window and renderer");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

const char* GameWindowException::what() const _NOEXCEPT {
    return message;
}
