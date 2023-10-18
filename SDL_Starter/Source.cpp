#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* helloWorld = NULL;
#undef main
bool init()
{
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("T_T i cry coz SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else {
            window = SDL_CreateWindow("SDL Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL)
            {
                printf("Window no want! SDL_Error: %s\n", SDL_GetError());
                return false;
            }
            else {
                screenSurface = SDL_GetWindowSurface(window);
                return true;
                
            }
        }
}

bool loadMedia(string mediaLocation) {
    helloWorld = SDL_LoadBMP(mediaLocation.c_str());
    if (helloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", mediaLocation.c_str(), SDL_GetError());
        return false;
    }
    return true;
}

void cleanUpSDL() {
    SDL_FreeSurface(helloWorld);
    helloWorld = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char* args[]) {
    /*int a = 12;
    
    cout<< to_string(a)<< "hi!" << '\n';
    char input;
    cin>>input;*/
    
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!loadMedia("bitmap1.bmp")) {
            printf("Failed to load media!\n");
        }
        else {
            SDL_BlitSurface(helloWorld,NULL,screenSurface,NULL);
            SDL_UpdateWindowSurface(window);
            //SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

        }
    }
    cin.get();
    cleanUpSDL();
    return 0;;
}