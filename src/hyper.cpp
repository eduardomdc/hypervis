#include "hyper.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include "algebra.hpp"
#include "draw.hpp"
#include "geometry.hpp"
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

Hyper::Hyper(int dimension){
    this->dimension = dimension;
    running = true;
    window = nullptr;
    renderer = nullptr;
    object cube = makeNCube(0.5, dimension);
    objects.push_back(cube);
    changedObjects.push_back(cube);
    angle = 0;
    angSpeed = 0.1;
    std::vector<pointnd> axy; 
    rotBasis = defaultbasis(dimension);
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
    
    TTF_Init();
    if (!TTF_WasInit()){
        cout<<"SDL_TTF error"<<endl;
        return;
    }
    font = TTF_OpenFont("../roboto.ttf", 20);
    cout<<"SDL OK!"<<endl;
    setDimension(2);
}

void Hyper::render(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i=0; i<changedObjects.size(); i++){
        drawObject(changedObjects[i], renderer);
    }
    drawBasis(rotBasis, renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(text, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {0, 0, texW, texH};
    SDL_RenderCopy(renderer, text, NULL, &dstrect);
    SDL_RenderPresent(renderer);
}

void Hyper::update(Uint32 dt){
    angle += angSpeed*dt;
    changedObjects[0] = objBasisTransform(objects[0], rotBasis);
}


void Hyper::quit(){
    cout<<"Closing systems..."<<endl;
    running = false;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
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
            case SDLK_x:
                angSpeed = angSpeed*2;
                break;
            case SDLK_z:
                angSpeed = angSpeed*0.5;
                break;
            case SDLK_w:
                if(dimension>2){
                    rotBasis = rotateBasis(rotBasis, {1,2}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_s:
                if (dimension>2){
                    rotBasis = rotateBasis(rotBasis, {1,2}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_d:
                if (dimension>2){
                    rotBasis = rotateBasis(rotBasis, {0,2}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_a:
                if (dimension>2){
                    rotBasis = rotateBasis(rotBasis, {0,2}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_q:
                if (dimension>1){
                    rotBasis = rotateBasis(rotBasis, {0,1}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_e:
                if (dimension>1){
                    rotBasis = rotateBasis(rotBasis, {0,1}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_i:
                if (dimension>3){
                    rotBasis = rotateBasis(rotBasis, {1,3}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_k:
                if (dimension>3){
                    rotBasis = rotateBasis(rotBasis, {1,3}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_j:
                if (dimension>3){
                    rotBasis = rotateBasis(rotBasis, {0,3}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_l:
                if (dimension>3){
                    rotBasis = rotateBasis(rotBasis, {0,3}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_o:
                if (dimension>3){
                    rotBasis = rotateBasis(rotBasis, {2,3}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_u:
                if (dimension>3){
                    rotBasis = rotateBasis(rotBasis, {2,3}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_h:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {0,4}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_f:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {0,4}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_t:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {1,4}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_g:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {1,4}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_y:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {2,4}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_r:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {2,4}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_v:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {3,4}, -angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_b:
                if (dimension>4){
                    rotBasis = rotateBasis(rotBasis, {3,4}, angSpeed);
                    rotBasis = reorthogonalize(rotBasis);
                }
                break;
            case SDLK_m:
                if (dimension<5)
                setDimension(dimension+1);
                break;
            case SDLK_n:
                if (dimension>2)
                setDimension(this->dimension-1);
                break;
            }
        }
    }
}

void Hyper::setDimension(int dimension){
    this->dimension = dimension;
    rotBasis = defaultbasis(dimension);
    object cube = makeNCube(0.5, dimension);
    objects[0] = cube;
    changedObjects[0] = cube;
    char str[200];
    sprintf(str, "%d-dimensional cube\n\n\n\n\nControls\n-------\nchange dimensions\n N,M\n\nrotations\n QWE RTY UIO\n ASD FGH JKL\n     VB\nchange speed\nZ,X", dimension);
    text = writeText(str, {255,255,255,255});
}
