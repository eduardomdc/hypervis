#include "hyper.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include "algebra.hpp"
#include "draw.hpp"
#include "geometry.hpp"
#include <iostream>
#include <vector>

using namespace std;

Hyper::Hyper(){
    running = true;
    window = nullptr;
    renderer = nullptr;
    object cube = makeCube(0.5);
    objects.push_back(cube);
    changedObjects.push_back(cube);
    angle = 0;
    angSpeed = 0.0001;
    std::vector<pointnd> axy; 
    pointnd axis;
    axis.dim = 3;
    axis.vec = {1, 2, 0};
    renormalize(&axis);
    axy.push_back(axis);
    rotBasis = orthogonalbasis(axy);
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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i=0; i<changedObjects.size(); i++){
        drawObject(changedObjects[i], renderer);
    }
    drawBasis(rotBasis, renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}

void Hyper::update(Uint32 dt){
    angle += angSpeed*dt*20;
    changedObjects[0] = rotateObj(objects[0], rotBasis, angle);
    SDL_RenderPresent(renderer);
}


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
