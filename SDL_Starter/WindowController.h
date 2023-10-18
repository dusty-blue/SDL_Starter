#pragma once
#include <string>
#include <SDL.h>
class WindowController
{
public:
    WindowController(int width, int height);
    ~WindowController();
    void loadMedia(std::string mediaLocation);
private:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Surface* loadedImg;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
};

