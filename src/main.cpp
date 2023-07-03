#include "main.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>

int main(){
    std::cout<<"Initializing..."<<std::endl;
    Hyper* hyper = new Hyper(); 
    hyper->initSDL(WIDTH, HEIGHT);
    Uint32 time = SDL_GetTicks();
    Uint32 delta;
    Uint32 spf = 1000/FPS;
    while(hyper->running){
        hyper->render();
        delta = SDL_GetTicks()-time;
        hyper->update(delta);
        hyper->input();
        if (delta < spf){
            SDL_Delay(spf-delta);
        }
        time = SDL_GetTicks();
    }
    std::cout<<"Exiting..."<<std::endl;
    return 0;
}
