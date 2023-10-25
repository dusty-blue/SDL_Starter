#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <SDL.h>
#include "WindowController.h"
#include <map>
#include <SDL_image.h>
#include <functional>
#include "Entity.h"

#include <Eigen/Dense>


void cleanUp() {
    std::cout<< "Let me just ge my broom...\n";
    IMG_Quit();
    SDL_Quit();
}

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video subsytem intialisation failed. SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Failed to intialise PNG library. SDL_Error %s\n",SDL_GetError());
        exit(1);
    } 
    
    
}

void printIK (int i, int k) {
    std::cout << i << "+" << k << "=" << (k + i) << "\n";
};

void printKey(SDL_KeyCode k) {
    
    std::cout << SDL_GetKeyName(k) << " is great!\n";
}

void assignKeybind(SDL_Event e, SDL_KeyCode k) {
    if (e.key.keysym.sym == k) {
        printKey(k);
    }
}



int main(int argc, char* args[]) {
    
    
    std::function<void()> printMe = [] {printKey(SDLK_u);};

    init();
    std::atexit(cleanUp);
    bool running = true;

    std::map<int, WindowController*> ctrlMap;
    WindowController winCtrl(640, 480);
    ctrlMap.insert({ winCtrl.windowID,&winCtrl });
    
    Entity player;
    
    player.texture = winCtrl.loadTexture("Pixil-Frame-1.png");
    SDL_Event e;
    std::function<void(SDL_Event)> boundKeyF = [](SDL_Event e) {assignKeybind(e, SDLK_u); };
    
        
    while(running) {
        
        
        winCtrl.prepareRenderer();
        const Eigen::Vector2d down = Eigen::Vector2d(0,1);
        const Eigen::Vector2d up = Eigen::Vector2d(0, -1);
        const Eigen::Vector2d left = Eigen::Vector2d(-1, 0);
        const Eigen::Vector2d right = Eigen::Vector2d(1, 0);


        while (SDL_PollEvent(&e) != 0) {
            switch (e.type)
            {
            //default:
            
            case SDL_QUIT:
                std::cout << "SDL_QUIT triggered\n";
                running = false;
                exit(0);
                break;
            case SDL_MOUSEMOTION:
                //std::cout << e.motion.x;
                //ctrlMap[e.window.windowID]->showRedCircle(e.motion.x,e.motion.y);
                break;
            case SDL_KEYDOWN:

                switch (e.key.keysym.sym) {
                    case SDLK_w:
                    
                    player.velocity = up;
                    break;
                    case SDLK_s:
                    player.velocity = down;
                    break;
                    case SDLK_d:
                    player.velocity = right;
                    break;
                    case SDLK_a:
                    player.velocity = left;
                    break;
                    case SDLK_p:
                    boundKeyF = [](SDL_Event e) { assignKeybind(e,SDLK_i);};
                    break;
                    case SDLK_z:
                    printMe();
                    break;
                }


            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    ctrlMap[e.window.windowID]->closeWindow();
                }
                
                break;

            }
            boundKeyF(e);
            
        }
        //std::cout << "Error in event queue" << SDL_GetError() << endl;
                
        //multi windows?
        winCtrl.update(&player);
        
        SDL_Delay(16);
        
    }

    
    

    return 0;
}