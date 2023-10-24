#include "MediaManager.h"
#include <SDL.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL_image.h>


MediaManager::MediaManager()
{
    defaultSurface = SDL_LoadBMP("bitmap3.bmp");
    if (defaultSurface) {
        std::cout << "Default surface loaded";
    }
    else {
        printf("Unable to load default texture. Error %s\n", SDL_GetError());
       
    }
}


MediaManager::~MediaManager()
{
    SDL_FreeSurface(defaultSurface);
    defaultSurface = NULL;
}

SDL_Surface* MediaManager::loadDefault() {
    SDL_Surface* temp = NULL; 
    temp = SDL_LoadBMP("bitmap3.bmp");
    if (temp) {
        return temp;
    }
    else {
        printf("Unable to load default texture. Error %s\n", SDL_GetError());
        return NULL;
    }
}
SDL_Texture * MediaManager::loadTexture(std::string path)
{
    return nullptr;
}
SDL_Surface * MediaManager::loadBMP(std::string path)
{
    return defaultSurface;
}

SDL_Surface * MediaManager::loadPNG(std::string path)
{
    SDL_Surface* loadedPNG = IMG_Load(path.c_str());
        if (loadedPNG) {
            return loadedPNG;
        }
        else {
            std::cout << "Unable to load image! SDL Error:" << SDL_GetError() << "\n";
            return defaultSurface;
        }
    
}
