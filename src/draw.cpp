#include "draw.hpp"
#include "geometry.hpp"
#include "main.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

SDL_Point atScreen(pointnd p){
    SDL_Point point;
    point.x = int((p.vec[0]/(p.vec[2]+1.1))*HEIGHT/2+int(WIDTH/2));
    point.y = int(-(p.vec[1]/(p.vec[2]+1.1))*HEIGHT/2+int(HEIGHT/2));
    return point;
}

void drawLine(pointnd a, pointnd b, SDL_Renderer* renderer){
    SDL_Point pa = atScreen(a); 
    SDL_Point pb = atScreen(b);
    SDL_RenderDrawLine(renderer, pa.x, pa.y, pb.x, pb.y);
}

void drawObject(object obj, SDL_Renderer* renderer){
    for (int i=0; i<obj.numPoints; i++){
        SDL_Point point = atScreen(obj.points[i]);
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }
    for (int i=0; i<obj.edges.size(); i++){
        drawLine(obj.points[obj.edges[i].idxa], obj.points[obj.edges[i].idxb], renderer);
    }
}

void drawBasis(std::vector<pointnd> basis, SDL_Renderer *renderer){
    std::vector<short> colors = {255,0,0};
    SDL_Point origin = atScreen({{0,0},2});
    for(int i=0; i<basis.size(); i++){
        SDL_SetRenderDrawColor(renderer,colors[i%3],colors[(i+1)%3],colors[(i+2)%3],255);
        SDL_Point point = atScreen(basis[i]);
        SDL_RenderDrawLine(renderer, origin.x, origin.y, point.x, point.y);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
