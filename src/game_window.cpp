#include "SDL2/SDL.h"
#include "game_window.h"
#include <stdexcept>

GameWindow::GameWindow() {
	int status = SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	if (status == -1) {
		throw GameWindowCreationException("Failed to create game window and renderer");
	}
}

GameWindow::~GameWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int GameWindow::getPixelWidth() {
	return widthPixels;
}

int GameWindow::getPixelHeight() {
	return heightPixels;
}

void GameWindow::clear() {
	SDL_SetRenderDrawColor(renderer, pixelOffColor.r, pixelOffColor.g, pixelOffColor.b, 0xFF);
	SDL_RenderClear(renderer);
}

void GameWindow::turnPixelOff(int pixelX, int pixelY) {
	setPixel(pixelX, pixelY, pixelOffColor);
}

void GameWindow::turnPixelOn(int pixelX, int pixelY) const {
	setPixel(pixelX, pixelY, pixelOnColor);
}

void GameWindow::setPixel(int pixelX, int pixelY, const SDL_Color& color) const
{
	if (pixelX < 0 || pixelX >= widthPixels ||
		pixelY < 0 || pixelY >= heightPixels) {
		return;
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
	SDL_Rect pixel{ pixelX * pixelSize, pixelY * pixelSize, pixelSize, pixelSize };
	SDL_RenderFillRect(renderer, &pixel);
}

void GameWindow::update() {
	SDL_RenderPresent(renderer);
}
