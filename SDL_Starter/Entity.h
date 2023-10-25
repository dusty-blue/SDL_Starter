#pragma once
#include <SDL.h>
#include <Eigen/Core>
class Entity
{
public:
    Entity();
    ~Entity();
    SDL_Texture* texture;
    Eigen::Vector2d position;
    Eigen::Vector2d velocity;
    void updatePosition(); 
    
    
};

