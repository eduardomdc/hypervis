#include "hyper.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include "draw.hpp"
#include "geometry.hpp"
#include <iostream>

using namespace std;

Hyper::Hyper(){
    running = true;
    window = nullptr;
    renderer = nullptr;
    object cube = makeCube(100);
    objects.push_back(cube);
}

void Hyper::initSDL(int width, int height){
    cout<<"Starting SDL"<<endl;
    window = SDL_CreateWindow("Hypervision", 
            0,
            0, 
            width, 
            height, 
            0);
    if (!window){
        cout<<"SDL window error"<<endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        cout<<"SDL renderer error"<<endl;
        return;
    } 
    cout<<"SDL OK!"<<endl;
}

void Hyper::render(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    drawLine({-100, 100}, {100,100}, renderer);
    rotateAroundX(objects[0], 0.01);
    drawObject(objects[0], renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Hyper::update(Uint32 dt){}

void Hyper::quit(){
    cout<<"Closing systems..."<<endl;
    running = false;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout<<"SDL killed"<<endl;
}

void Hyper::input(){
    SDL_Event current;
    while(SDL_PollEvent(&current)){
        switch (current.type) {
        case SDL_QUIT:
            quit();
        }
    }
}
