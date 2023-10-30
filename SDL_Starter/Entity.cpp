#include "Entity.h"
#include <Eigen/Core>
#include <iostream>

Entity::Entity()
{
    texture = NULL;
    position = Eigen::Vector2<int>::Zero();
}


Entity::~Entity()
{
    SDL_DestroyTexture(texture);
    texture = NULL;
}
/*
Adds velocity to position. Wraps position to screen boundaries
*/
void Entity::updatePosition(int screenHeight, int screenWidth) {
    position += velocity;
    position[0] = moduloHelper(position[0], screenWidth);
    position[1] = moduloHelper(position[1], screenHeight);

    }

int Entity::moduloHelper(int x, int d) {
    return ((x%d)+d)%d;
}



TrailEntity::TrailEntity() {
    length= 20;
    head.position = position;
    head.next = new BodyPart;
    head.next->position = Eigen::Vector2<int>::Zero();
    head.next->next = NULL;
    BodyPart* current = &head;
    for (int i = 0; i < length; i++) {
        current->next = new BodyPart;
        current = current->next;
        current->position = Eigen::Vector2<int>::Zero();
        current->next = NULL;
    }
}

TrailEntity::~TrailEntity()
{
}

/*
Adds velocity to position. Wraps position to screen boundaries
*/
void TrailEntity::updatePosition(int screenHeight, int screenWidth) {
    position += velocity;

    position[0] = moduloHelper(position[0], screenWidth);
    position[1] = moduloHelper(position[1], screenHeight);
    
    head.position = position;
    BodyPart* current = &head;
    Eigen::Vector2<int> posPrev = current->position;
    Eigen::Vector2<int> posNext = current->position;
    while (current->next) {
        current = current->next;
        posNext = current->position;
        current->position = posPrev;
        posPrev = posNext;
    }


}

GridEntity::GridEntity() {
    cols = 1;
    rows = 1;
    grid = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>();
    grid.resize(cols, rows);
    grid.Zero(cols, rows);
}

GridEntity::GridEntity(int cols, int rows, int cellSize) {
    this->cols = cols;
    this->rows = rows;
    this->cellSize = cellSize;
    this->grid = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic>();

    grid.resize(cols,rows);
    grid.Zero(cols,rows);

}

void GridEntity::setGridCell(int x, int y, int value) {
    grid(x,y) = value;
    
}

void GridEntity::forAllCells(std::function<int(int)> func) {
    grid.unaryExpr(func);
    

}