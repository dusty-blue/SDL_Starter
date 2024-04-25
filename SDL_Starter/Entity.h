#pragma once
#include <SDL.h>
#include <Eigen/Core>
#include <memory>
#include "WindowController.h"
#include <list>

struct BodyPart {
    Eigen::Vector2f position;
    std::unique_ptr<BodyPart> next;
} ;
class Entity
{
public:
    Entity();
    ~Entity();
    SDL_Texture* texture;
    Eigen::Vector2f position;
    Eigen::Vector2f velocity;
    //upadtePosition is temporary
    void updatePosition(int screenHeight, int screenWidth);
    virtual void Draw(WindowController& winCtrl) = 0;
    //virtual void Move(Eigen::Vector2i t)=0;
    //virtual void Add(std::unique_ptr<Entity> entity ) {};
    //virtual void Remove(std::unique_ptr<Entity> entity) {};
    virtual bool IsComposite() const {
        return false;
    }
    void blit(SDL_Renderer* renderer, int s);

    void blit(SDL_Renderer* renderer, int x, int y, int s);

    SDL_Point GetTextureSize();

    
protected:
    int moduloHelper(int x, int d);
    float moduloHelper(float x, float d);
    Entity* parent;
    void SetParent(Entity* parent);

    
};

class CompositeEntity : public Entity {
    protected:
    std::list<std::unique_ptr<Entity>> children;
    
};

class RootEntity : public Entity {

};

class GridEntity : public Entity {
public:
    GridEntity();
    GridEntity(int cols, int rows, int cellSize);
    void setGridCell(int x, int y, int value);
    void forAllCells(std::function<int(int)> func);
    void forAllCells(std::function<void(SDL_Texture* texture, int x, int y)>func);
    void Draw(WindowController & winCtrl);
    bool IsComposite() const;
    private:
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> grid;
    int cols,rows, cellSize;

};

class TrailEntity : public Entity {
public:

    TrailEntity();
    ~TrailEntity();
    void Draw(WindowController& renderer);
    void updatePosition(int screenHeight, int screenWidth);
    std::unique_ptr<BodyPart> head;
protected:
    int length;
};
