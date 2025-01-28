#ifndef SDL_HPP
#define SDL_HPP

#include <SDL2/SDL.h>

/**
 * @brief Manages SDL initialization and rendering resources.
 */
class Sdl {
public:
    SDL_Window* window; /**< SDL Window */
    SDL_Renderer* renderer; /**< SDL Renderer */

    /**
     * @brief Constructor for Sdl.
     * @param title The window title.
     * @param width The window width.
     * @param height The window height.
     */
    Sdl(const char* title, int width, int height);

   /**
    * @brief Destructor for Sdl.
    */
    ~Sdl();
};

#endif