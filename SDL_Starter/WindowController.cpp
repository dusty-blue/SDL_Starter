#include "WindowController.h"
#include <SDL.h>

#include <stdio.h>
#include <iostream>
#include <string>

WindowController::WindowController(int width, int height):SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{   
    window = NULL;
    screenSurface = NULL;
    loadedImg = NULL;
    hidden = false;
    window = SDL_CreateWindow("SDL Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window)
    {
        windowID = SDL_GetWindowID(window);
        //screenSurface = SDL_GetWindowSurface(window);
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        }
        else {
            printf("Creating Renderer Failed. SDL_Error: %s\n", SDL_GetError());
        }

    }
    else {
        printf("Window no want! SDL_Error: %s\n", SDL_GetError());
        
    }
}

WindowController::~WindowController()
{
    SDL_FreeSurface(loadedImg);
    loadedImg = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
}

SDL_Surface* WindowController::loadBMP(std::string mediaLocation)
{
    loadedImg = SDL_LoadBMP(mediaLocation.c_str());
    if (loadedImg)
    {
        return loadedImg;      
            }
    else {
        printf("Unable to load image %s! SDL Error: %s\n", mediaLocation.c_str(), SDL_GetError());
       //TO DO add default surface
        std::cin.get();
    }
    
}

SDL_Surface* WindowController::loadSurface(std::string path) {
    SDL_Surface* surface = NULL;
    surface = SDL_ConvertSurface(loadBMP(path),screenSurface->format ,0 );
    if(surface) {
        return surface;
        }
    else {
        printf("Unable to create converted surface. Error: %s\n", SDL_GetError());
        //TO DO add default surface
       std::cin.get();
    }
}

SDL_Surface * WindowController::loadSurface(SDL_Surface * input)
{
    SDL_Surface* surface = NULL;
    surface = SDL_ConvertSurface(input, screenSurface->format, 0);
    if (surface) {
        return surface;
    }
    else {
        printf("Unable to create converted surface. Error: %s\n", SDL_GetError());
        //TO DO add default surface
        std::cin.get();
    }
    return nullptr;
}

void WindowController::showSurface(SDL_Surface* surface) {

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    if (surface) {
        SDL_BlitScaled(loadSurface(surface), NULL, screenSurface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }
    else {
        std::cout << "Input was a null ptr. ts ts ts\n";
    }
    
}

void WindowController::showRedCircle(int x, int y) {
    SDL_Surface* redCircle = loadSurface("red_circle.bmp");
    SDL_Rect boundingBox;
    boundingBox.x = x;
    boundingBox.y = y;
    boundingBox.w = redCircle->w;
    boundingBox.h = redCircle->h;
    SDL_BlitScaled(redCircle,NULL,screenSurface,&boundingBox);
    SDL_UpdateWindowSurface(window);
}

void WindowController::loadMedia(std::string path) {
    showSurface(loadSurface(path));
}

void WindowController::update() {
    /*
    Stub
    */

}

void WindowController::closeWindow() {
    SDL_DestroyWindow(window);
    window = NULL;
}

