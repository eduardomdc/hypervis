#include "main.hpp"
#include <iostream>
#include <SDL2/SDL.h>

#define WIDTH 480
#define HEIGHT 480
#define FPS 60

int main(){
    std::cout<<"Initializing..."<<std::endl;
    Hyper* hyper = new Hyper(); 
    hyper->initSDL(WIDTH, HEIGHT);
    while(hyper->running){
        hyper->render();
        hyper->update();
        hyper->input();
    }
    std::cout<<"Exiting..."<<std::endl;
    return 0;
}
