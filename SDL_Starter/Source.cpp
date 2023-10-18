#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <SDL.h>
#include "WindowController.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gwindow = NULL;
SDL_Surface* gscreenSurface = NULL;
SDL_Surface* ghelloWorld = NULL;
#undef main
bool init()
{
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("T_T i cry coz SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else {
            gwindow = SDL_CreateWindow("SDL Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (gwindow == NULL)
            {
                printf("Window no want! SDL_Error: %s\n", SDL_GetError());
                return false;
            }
            else {
                gscreenSurface = SDL_GetWindowSurface(gwindow);
                return true;
                
            }
        }
}

bool loadMedia(string mediaLocation) {
    ghelloWorld = SDL_LoadBMP(mediaLocation.c_str());
    if (ghelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", mediaLocation.c_str(), SDL_GetError());
        return false;
    }
    return true;
}

void cleanUpSDL() {
    SDL_FreeSurface(ghelloWorld);
    ghelloWorld = NULL;
    SDL_DestroyWindow(gwindow);
    gwindow = NULL;
    SDL_Quit();
}

int main(int argc, char* args[]) {
    /*int a = 12;
    
    cout<< to_string(a)<< "hi!" << '\n';
    char input;
    cin>>input;*/
    WindowController winCtrl(640,480);
    winCtrl.loadMedia("bitmap1.bmp");

    
    //if (!init()) {
    //    printf("Failed to initialize!\n");
    //}
    //else {
    //    if (!loadMedia("bitmap1.bmp")) {
    //        printf("Failed to load media!\n");
    //    }
    //    else {
    //        SDL_BlitSurface(helloWorld,NULL,screenSurface,NULL);
    //        SDL_UpdateWindowSurface(window);
    //        //SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

    //    }
    //}


    cin.get();
    //cleanUpSDL();
    return 0;;
}