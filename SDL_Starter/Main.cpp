#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <SDL.h>
#include "WindowController.h"
#include <map>
#include <SDL_image.h>
#include <functional>
#include "MediaManager.h"

void cleanUp() {
    std::cout<< "Let me just ge my broom...\n";
    IMG_Quit();
    SDL_Quit();
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video subsytem intialisation failed. SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Failed to intialise PNG library. SDL_Error %s\n",SDL_GetError());
        return false;
    } 
    
    return true;
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
    /*int a = 12;
    cout<< to_string(a)<< "hi!" << '\n';
    char input;
    cin>>input;*/
    std::atexit(cleanUp);
    //auto customA =customFun(2);
    int a = 5;
    auto printI = [&a](auto b) { printIK(b, a);};
    a =6;
    printI(3);
    std::function<void()> printMe = [] {printKey(SDLK_u);};
    
    
    


    if (!init()) {
        printf("T_T i cry coz SDL_Error: %s\n", SDL_GetError());
    } 
    else {
        std::map<int,WindowController*> ctrlMap;
        WindowController winCtrl(640, 480);
        ctrlMap.insert({winCtrl.windowID,&winCtrl});
        MediaManager MediaManager;

        //winCtrl.loadMedia("bitmap3.bmp");
        winCtrl.showSurface(MediaManager.loadPNG("Pixil-Frame-1.png"));
        /*WindowController winCtrl2(100,100);
        ctrlMap.insert({winCtrl2.windowID,&winCtrl2});
        
        winCtrl2.loadMedia("bitmap2.bmp");*/
        struct Coords {
            int x= 320;
            int y = 240;
        };

        Coords redCircleCoords;
        winCtrl.showRedCircle(redCircleCoords.x,redCircleCoords.y);
        SDL_Event e;
        std::function<void(SDL_Event)> boundKeyF =[](SDL_Event e) {assignKeybind(e, SDLK_u);};

        while (SDL_WaitEvent(&e) != 0) {
            switch (e.type)
            {
            //default:
            //    /*winCtrl.update();
            //    winCtrl2.update();*/
            //    break;
            
            case SDL_QUIT:
                std::cout << "SDL_QUIT triggered\n";
                exit(0);
                break;
            case SDL_MOUSEMOTION:
                //std::cout << e.motion.x;
                //ctrlMap[e.window.windowID]->showRedCircle(e.motion.x,e.motion.y);
                break;
            case SDL_KEYDOWN:

                switch (e.key.keysym.sym) {
                    case SDLK_w:
                    
                    redCircleCoords.y -= 1;
                    winCtrl.showRedCircle(redCircleCoords.x,redCircleCoords.y);
                    break;
                    case SDLK_s:
                    redCircleCoords.y += 1;
                    winCtrl.showRedCircle(redCircleCoords.x, redCircleCoords.y);
                    break;
                    case SDLK_d:
                    redCircleCoords.x += 1;
                    winCtrl.showRedCircle(redCircleCoords.x, redCircleCoords.y);
                    break;
                    case SDLK_a:
                    redCircleCoords.x -= 1;
                    winCtrl.showRedCircle(redCircleCoords.x, redCircleCoords.y);
                    break;
                    case SDLK_p:
                    //printMe = [] {printKey(SDLK_i); };
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
        std::cout << "Error in event queue" << SDL_GetError() << endl;
        
        
        
        //WindowController winCtrl2(100,100);
        
        //multi windows?
        

        
    }

    
    

    return 0;;
}