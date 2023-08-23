#ifndef HYPER
#define HYPER
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "geometry.hpp"

class Hyper {
public:
    Hyper(int dimension);
    void initSDL(int width, int height);
    void render();
    void update(Uint32 dt);
    void input();
    void quit();
    void setDimension(int dimension);
    bool running;
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* font;
    SDL_Texture* text;
    std::vector<object> objects;
    std::vector<object> changedObjects;
    std::vector<pointnd> rotBasis;
    float angle;
    float angSpeed;
    int dimension;
};

extern Hyper* hyper;

#endif
