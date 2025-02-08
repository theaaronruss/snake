#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "SDL3/SDL.h"
#include <exception>

class GameWindow {
    private:
        static constexpr const char* title { "Snake" };
        static constexpr int width { 640 };
        static constexpr int height { 480 };
        static constexpr SDL_Color backgroundColor { 0x00, 0x00, 0x00 };
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        GameWindow();
        ~GameWindow();
        void clear();
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
