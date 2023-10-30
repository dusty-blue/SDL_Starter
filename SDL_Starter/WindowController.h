#pragma once
#include <string>
#include <SDL.h>
#include "Entity.h"
class WindowController
{
public:
    WindowController(int width, int height);
    ~WindowController();
    
    void loadMedia(std::string mediaLocation);
    /*Loads a BMP to a surface which is formatted to match the screenSurface format.*/
    SDL_Surface * loadSurface(std::string path);

    /*Returns the input surface to screenSurface format*/
    SDL_Surface* loadSurface(SDL_Surface* input);

    /*Stretches the input to window size and Blit it to the screensurface*/
    void showSurface(SDL_Surface * surface);

    /*Displays a red circle BMp texture at the provided x,y coordinates*/
    void showRedCircle(int x, int y);

    /*Sets the render color and clears the render*/
    void prepareRenderer(void);

    /*Takes an entity as an input and displays its texture at its position*/
    void update(Entity* obj);

    /*Loads a Texture from the specified file path.*/
    SDL_Texture * loadTexture(std::string path);
    
    /*Destroys the window*/
    void closeWindow();
    /*SDL Window ID*/
    int windowID;
private:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;
    SDL_Surface* loadedImg;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
        
    SDL_Event e;

    /*Loads a BMP from file path*/
    SDL_Surface* loadBMP(std::string mediaLocation);

    void blit(SDL_Texture* texture, int x, int y);
};

