#include "Sdl.h"


/**
 * @brief Constructor for Sdl.
 * @param title The window title.
 * @param width The window width.
 * @param height The window height.
 */
Sdl::Sdl(const char* title, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RaiseWindow(window);
    SDL_SetWindowInputFocus(window);
}

/**
 * @brief Destructor for Sdl.
 */
Sdl::~Sdl() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

