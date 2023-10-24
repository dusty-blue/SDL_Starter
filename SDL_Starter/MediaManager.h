#pragma once
#include <SDL.h>

#include <stdio.h>
#include <iostream>
#include <string>

class MediaManager
{
public:
    MediaManager();
    ~MediaManager();
    SDL_Surface* loadBMP(std::string path);
    SDL_Surface* loadPNG(std::string path);
    SDL_Surface* loadDefault();
    SDL_Surface* defaultSurface;
    SDL_Texture* loadTexture(std::string path);

    

};

