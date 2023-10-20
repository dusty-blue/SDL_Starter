#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include <SDL.h>
#include "WindowController.h"
#include <map>

void cleanUp() {
    std::cout<< "Let me just ge my broom...\n";
    SDL_Quit();
}



int main(int argc, char* args[]) {
    /*int a = 12;
    cout<< to_string(a)<< "hi!" << '\n';
    char input;
    cin>>input;*/
    std::atexit(cleanUp);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("T_T i cry coz SDL_Error: %s\n", SDL_GetError());
    } 
    else {
        std::map<int,WindowController*> ctrlMap;
        WindowController winCtrl(640, 480);
        ctrlMap.insert({winCtrl.windowID,&winCtrl});
        winCtrl.loadMedia("bitmap1.bmp");
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
        
        cout<< "found it\n";
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
                }


            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    ctrlMap[e.window.windowID]->closeWindow();
                }
                
                break;

            }
            
            
        }
        std::cout << "Error in event queue" << SDL_GetError() << endl;
        
        
        
        //WindowController winCtrl2(100,100);
        
        //multi windows?
        

        
    }
    

    return 0;;
}