#include "draw.hpp"
#include "geometry.hpp"
#include "main.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

SDL_Point atScreen(point2d p){
    SDL_Point point;
    point.x = int(p.x)+WIDTH/2;
    point.y = int(p.y)+HEIGHT/2;
    return point;
}

void drawLine(point2d a, point2d b, SDL_Renderer* renderer){
    SDL_Point pa = atScreen(a); 
    SDL_Point pb = atScreen(b);
    SDL_RenderDrawLine(renderer, pa.x, pa.y, pb.x, pb.y);
}

void drawObject(object obj, SDL_Renderer* renderer){
    for (int i=0; i<obj.numPoints; i++){
        point2d p2d = {obj.points[i].vec[0], obj.points[i].vec[1]};
        SDL_Point point = atScreen(p2d);
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }
}
