#include "Entity.h"
#include <Eigen/Core>
#include <iostream>

Entity::Entity()
{
    texture = NULL;
    position = Eigen::Vector2d::Zero();
}


Entity::~Entity()
{
    SDL_DestroyTexture(texture);
    texture = NULL;
}
/*
Adds velocity to position. Wraps position to screen boundaries
*/
void Entity::updatePosition() {
    position += velocity;
    //TO DO Modulo if x,y is negative 
    position[0] = std::fmod(position[0], 640.0) ;
    position[1] = std::fmod(position[1], 480.0);

}

