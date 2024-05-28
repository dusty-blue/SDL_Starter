#include <stdio.h>

#include "single_random_entity.h"
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

//test



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
    WindowController winCtrl(512, 512);
    ctrlMap.insert({ winCtrl.windowID,&winCtrl });
    
    TrailEntity player;
    //GridEntity grid(8,8,64);
    
    //TO DO : Change background Color
    single_random_entity treat(winCtrl.getWindowSize().x(), winCtrl.getWindowSize().y());
    treat.Draw(winCtrl);
	treat.texture = winCtrl.loadTexture(("RainbowBucket_small.png"));
    

    player.Draw(winCtrl);
    player.texture = winCtrl.loadTexture("Pixil-Frame-small.png");
    SDL_Event e;
    std::function<void(SDL_Event)> boundKeyF = [](SDL_Event e) {assignKeybind(e, SDLK_u); };
    

    
        
    while(running) {
        
        
        winCtrl.prepareRenderer();
        const Eigen::Vector2f down = Eigen::Vector2f(0,2);
        const Eigen::Vector2f up = Eigen::Vector2f(0, -2);
        const Eigen::Vector2f left = Eigen::Vector2f(-2, 0);
        const Eigen::Vector2f right = Eigen::Vector2f(2, 0);


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
					case SDLK_t:
					player.increaseLength(1);
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
        if((treat.position - player.position).norm()<64)
        {
            player.increaseLength(1);
            treat.NewRandomLocation();
        }
        //std::cout << "Error in event queue" << SDL_GetError() << endl;
                
        //multi windows?
        //winCtrl.update(&player);
        treat.Draw(winCtrl);
        player.Draw(winCtrl);
        SDL_RenderPresent(winCtrl.getRenderer());
        
        SDL_Delay(16);
        
    }

    return 0;
}