#ifndef HYPER
#define HYPER
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <vector>
#include "geometry.hpp"

class Hyper {
public:
    Hyper();
    void initSDL(int width, int height);
    void render();
    void update(Uint32 dt);
    void input();
    void quit();
    bool running;
    SDL_Renderer* renderer;
    SDL_Window* window;
    std::vector<object> objects;
    std::vector<object> changedObjects;

    std::vector<pointnd> rotBasis;
    float angle;
    float angSpeed;
};

extern Hyper* hyper;

#endif
