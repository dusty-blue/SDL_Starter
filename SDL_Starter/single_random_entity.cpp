#include "single_random_entity.h"
#include <random>

single_random_entity:: single_random_entity(float maxX, float maxY) : distX(0.0, maxX), distY(0.0, maxY)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	//std::uniform_real_distribution<> distX(0.0, maxX);
	//std::uniform_real_distribution<> distY(0.0, maxY);
	this->position[0] = distX(rng);
	this->position[1] = distY(rng);
}

bool single_random_entity::IsComposite() const { return false; }

void single_random_entity::Draw(WindowController& winCtrl)
{
	this->blit(winCtrl.getRenderer(), 1);
}

void single_random_entity::NewRandomLocation()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	this->position[0] = distX(rng);
	this->position[1] = distY(rng);
}