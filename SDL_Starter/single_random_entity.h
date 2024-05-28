#pragma once
#include <random>

#include "Entity.h"
class single_random_entity : public Entity
{
public:
    single_random_entity(float x, float y);
    std::uniform_real_distribution<> distX;
    std::uniform_real_distribution<> distY;
    bool IsComposite() const;
    void Draw(WindowController& winCtrl);
    void NewRandomLocation();
};

