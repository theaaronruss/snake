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
	SDL_SetRenderDrawColor(renderer, pixelOffColor.r, pixelOffColor.g, pixelOffColor.b, 0xFF);
	SDL_RenderClear(renderer);
}

void GameWindow::turnPixelOff(int pixelX, int pixelY) {
	setPixel(pixelX, pixelY, pixelOffColor);
}

void GameWindow::turnPixelOn(int pixelX, int pixelY) {
	setPixel(pixelX, pixelY, pixelOnColor);
}

void GameWindow::setPixel(int pixelX, int pixelY, const SDL_Color& color)
{
	if (pixelX < 0 || pixelX >= widthPixels ||
		pixelY < 0 || pixelY >= heightPixels) {
		return;
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_FRect pixel{ static_cast<float>(pixelX * pixelSize), static_cast<float>(pixelY * pixelSize), pixelSize, pixelSize };
	SDL_RenderFillRect(renderer, &pixel);
}

void GameWindow::update() {
	SDL_RenderPresent(renderer);
}
