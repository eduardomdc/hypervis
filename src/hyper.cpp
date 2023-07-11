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
    object cube = makeNCube(0.5, 3);
    objects.push_back(cube);
    changedObjects.push_back(cube);
    angle = 0;
    angSpeed = 0.0001;
    std::vector<pointnd> axy; 
    axy.push_back({{1,0,0,0}, 4});
    axy.push_back({{0,1,0,1},4});
    //rotBasis = orthogonalbasis(axy);
    rotBasis = defaultbasis(3);
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i=0; i<changedObjects.size(); i++){
        drawObject(changedObjects[i], renderer);
    }
    drawBasis(rotBasis, renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}

void Hyper::update(Uint32 dt){
    angle += angSpeed*dt;
    changedObjects[0] = rotateObj(objects[0], rotBasis, angle);
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
            break;
        case SDL_KEYDOWN:
            switch (current.key.keysym.sym){
            case SDLK_i:
                angSpeed = angSpeed*1.1;
                break;
            case SDLK_k:
                angSpeed = angSpeed*0.9;
                break;
            case SDLK_w:
                rotBasis = rotateBasis(rotBasis, {1,2}, 0.1);
                rotBasis = reorthogonalize(rotBasis);
                break;
            case SDLK_s:
                rotBasis = rotateBasis(rotBasis, {1,2}, -0.1);
                rotBasis = reorthogonalize(rotBasis);
                break;
            case SDLK_d:
                rotBasis = rotateBasis(rotBasis, {0,1}, -0.1);
                rotBasis = reorthogonalize(rotBasis);
                break;
            case SDLK_a:
                rotBasis = rotateBasis(rotBasis, {0,1}, 0.1);
                rotBasis = reorthogonalize(rotBasis);
                break;
            }
        }
    }
}
