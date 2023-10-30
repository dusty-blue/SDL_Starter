#include "Entity.h"
#include <Eigen/Core>
#include <iostream>

Entity::Entity()
{
    texture = NULL;
    position = Eigen::Vector2<int>::Zero();
    length=20;
    head.position = position;
    head.next = new BodyPart;
    head.next->position = Eigen::Vector2<int>::Zero();
    head.next->next = NULL;
    BodyPart* current = &head;
    for (int i=0; i < length; i++) {
        current->next = new BodyPart;
        current = current->next;
        current->position = Eigen::Vector2<int>::Zero();
        current->next = NULL;
    }
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
    /*position[0] = std::fmod(position[0], 640.0) ;
    position[1] = std::fmod(position[1], 480.0);*/

    position[0] = moduloHelper(position[0], 640);
    position[1] = moduloHelper(position[1], 480);

    head.position =position;
    BodyPart* current = &head;
    Eigen::Vector2<int> posPrev= current->position;
    Eigen::Vector2<int> posNext = current->position;
    while (current->next) {
        current = current->next;
        posNext = current->position;
        current->position = posPrev;
        posPrev = posNext;
    }


}

int Entity::moduloHelper(int x, int d) {
    return ((x%d)+d)%d;
}

