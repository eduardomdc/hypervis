#include "hyper.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

using namespace std;

Hyper::Hyper(){
    running = true;
    window = nullptr;
    renderer = nullptr;
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
   SDL_RenderPresent(renderer);
}

void Hyper::update(){}

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
