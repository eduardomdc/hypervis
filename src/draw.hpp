#ifndef DRAW
#define DRAW

#include "geometry.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

SDL_Point screenPoint(point2d p);
void drawLine(point2d a, point2d b, SDL_Renderer* renderer);
void drawObject(object obj, SDL_Renderer* renderer);

#endif