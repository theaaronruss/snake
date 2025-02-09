#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "SDL3/SDL.h"
#include <exception>

class GameWindow {
	private:
		static constexpr const char* title { "Snake" };
		static constexpr int pixelSize{ 20 };
		static constexpr int width{ pixelSize * 32 };
		static constexpr int height{ pixelSize * 24 };
		static constexpr int widthPixels{ width / pixelSize };
		static constexpr int heightPixels{ height / pixelSize };
		const SDL_Color pixelOffColor{ 0xC5, 0xCA, 0xA4 };
		const SDL_Color pixelOnColor{ 0x4A, 0x51, 0x38 };
		SDL_Window* window;
		SDL_Renderer* renderer;
		void setPixel(int pixelX, int pixelY, const SDL_Color& color);
	public:
		GameWindow();
		~GameWindow();
		void clear();
		void turnPixelOff(int pixelX, int pixelY);
		void turnPixelOn(int pixelX, int pixelY);
		void update();
};

class GameWindowCreationException {
	private:
		const char* message;
	public:
		GameWindowCreationException(const char* message) : message { message }{};
		const char* what() const { return message; };
};

#endif
