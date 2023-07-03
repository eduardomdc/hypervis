#ifndef HYPER
#define HYPER
#include <SDL2/SDL.h>

class Hyper {
public:
    Hyper();
    void initSDL(int width, int height);
    void render();
    void update();
    void input();
    void quit();
    bool running;
    SDL_Renderer* renderer;
    SDL_Window* window;
};

#endif
