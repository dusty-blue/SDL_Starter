#pragma once
#include <string>
#include <SDL.h>
class WindowController
{
public:
    WindowController(int width, int height);
    ~WindowController();
    SDL_Surface* loadBMP(std::string mediaLocation);
    void loadMedia(std::string mediaLocation);
    SDL_Surface * loadSurface(std::string path);
    void showSurface(SDL_Surface * surface);
    void showRedCircle(int x, int y);
    void update();
    void closeWindow();
    bool hidden;
    int windowID;
private:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Surface* loadedImg;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    
    SDL_Event e;
};

