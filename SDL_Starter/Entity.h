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
    void updatePosition(int screenHeight, int screenWidth);
    
protected:
    int moduloHelper(int x, int d);
    

};

class GridEntity : public Entity {
public:
    GridEntity();
    GridEntity(int cols, int rows, int cellSize);
    void setGridCell(int x, int y, int value);
    void forAllCells(std::function<int(int)> func);
    private:
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> grid;
    int cols,rows, cellSize;

};

class TrailEntity : public Entity {
public:

    TrailEntity();
    ~TrailEntity();
    void updatePosition(int screenHeight, int screenWidth);
    BodyPart head;
protected:
    int length;
};
