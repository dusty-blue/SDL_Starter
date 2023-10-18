#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#undef main
int main(int argc, char* args[]) {
    /*int a = 12;
    
    cout<< to_string(a)<< "hi!" << '\n';
    char input;
    cin>>input;*/
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("T_T i cry coz SDL_Error: %s\n", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow ("SDL Rules", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window no want! SDL_Error: %s\n", SDL_GetError());
        }
        else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,0xff,0xff,0xff));
            SDL_UpdateWindowSurface(window);
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }
    /*
    if (input == 'f')
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        cout<< "bye~";
        return 0;
    }*/
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;;
}