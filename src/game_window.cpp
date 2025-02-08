#include "SDL3/SDL.h"
#include "game_window.h"
#include <stdexcept>

GameWindow::GameWindow() {
    SDL_Log("Creating game window and renderer");
    bool success = SDL_CreateWindowAndRenderer(title, width, height, 0, &window, &renderer);
    if (!success) {
        throw GameWindowCreationException("Failed to create game window and renderer");
    }
}

GameWindow::~GameWindow() {
    SDL_Log("Destroying game window and renderer");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GameWindow::clear() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 0xFF);
    SDL_RenderClear(renderer);
}

void GameWindow::update() {
    SDL_RenderPresent(renderer);
}
