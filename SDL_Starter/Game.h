#pragma once
#include <Eigen/Dense>
#include "Entity.h"
class Game
{
public:
    Game();
    ~Game();
    void setTreat();
    void setSnake();
    void setLength();
    int getLength();
    bool updateGameState();

private:
    GridEntity snake;
    int snakeLength;
};

