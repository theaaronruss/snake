#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "SDL3/SDL.h"
#include <exception>

class GameWindow {
    private:
        static constexpr const char* title { "Snake" };
        static constexpr int width { 640 };
        static constexpr int height { 480 };
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        GameWindow();
        ~GameWindow();
};

class GameWindowException : public std::exception {
    private:
        const char* message;
    public:
        GameWindowException(const char* message) : message { message }{};
        const char* what() const _NOEXCEPT override;
};

#endif
