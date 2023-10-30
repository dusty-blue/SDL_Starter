#pragma once
#include <SDL.h>
#include <Eigen/Core>
struct BodyPart {
    Eigen::Vector2<int> position;
    BodyPart* next;    
} ;
class Entity
{
public:
    Entity();
    ~Entity();
    SDL_Texture* texture;
    Eigen::Vector2<int> position;
    Eigen::Vector2<int> velocity;
    void updatePosition();
    BodyPart head;
    
private:
    int moduloHelper(int x, int d);
    int length;

};

