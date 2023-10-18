#include "WindowController.h"
#include <SDL.h>

#include <stdio.h>
#include <string>

WindowController::WindowController(int width, int height):SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{   
    window = NULL;
    screenSurface = NULL;
    loadedImg = NULL;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("T_T i cry coz SDL_Error: %s\n", SDL_GetError());
        
    }
    else {
        window = SDL_CreateWindow("SDL Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window no want! SDL_Error: %s\n", SDL_GetError());
            
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
}

WindowController::~WindowController()
{
    SDL_FreeSurface(loadedImg);
    loadedImg = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
}

void WindowController::loadMedia(std::string mediaLocation)
{
    loadedImg = SDL_LoadBMP(mediaLocation.c_str());
    if (loadedImg == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", mediaLocation.c_str(), SDL_GetError());
        
    }
    else {
        SDL_BlitSurface(loadedImg, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }
    
}

