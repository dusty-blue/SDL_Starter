#include "Entity.h"
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <iostream>
#include <cmath>


//
//template<typename Func>
//struct lambda_as_visitor_wrapper : Func {
//    lambda_as_visitor_wrapper(const Func& f) : Func(f) {}
//    template<typename S, typename I>
//    void init(const S& v, I i, I j) { return Func::operator()(v, i, j); }
//};
//
//template<typename Mat, typename Func>
//void visit_lambda(const Mat& m, const Func& f)
//{
//    lambda_as_visitor_wrapper<Func> visitor(f);
//    m.visit(visitor);
//}

Entity::Entity()
{
    texture = NULL;
    position = Eigen::Vector2f::Zero();

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
    position[0] = moduloHelper(position[0], static_cast<float>(screenWidth));
    position[1] = moduloHelper(position[1], static_cast<float>(screenHeight));

    }

int Entity::moduloHelper(int x, int d) {
    return ((x%d)+d)%d;
}

float Entity::moduloHelper(float x, float d) {
    return std::fmod(std::fmod(x,d)+d,d);
}

void Entity::SetParent(Entity*  parent) {
    this->parent = parent; 
}

void Entity::blit(SDL_Renderer* renderer, int s) {
    SDL_Rect dest;
    dest.x = static_cast<int>(this->position.x());
    dest.y = static_cast<int>(this->position.y());
    SDL_QueryTexture(this->texture, NULL, NULL, &dest.w, &dest.h);
    dest.w *= s;
    dest.h *= s;
    SDL_RenderCopy(renderer,this-> texture, NULL, &dest);
}

void Entity::blit(SDL_Renderer* renderer, int x , int y,int s) {
    SDL_Rect dest;
    dest.x =x;
    dest.y = y;
    SDL_QueryTexture(this->texture, NULL, NULL, &dest.w, &dest.h);
    dest.w *= s;
    dest.h *= s;
    SDL_RenderCopy(renderer, this->texture, NULL, &dest);
}

SDL_Point Entity::GetTextureSize() {
    SDL_Point size;
    SDL_QueryTexture(this->texture, NULL, NULL, &size.x, &size.y);
    return size;
}
TrailEntity::TrailEntity() {
    length= 4;

    auto push = [&head=head](Eigen::Vector2f pos) {
        head = std::unique_ptr<BodyPart>(new BodyPart{pos, std::move(head)});
    };

    for (int i = 0; i < length; i++) {
        push(Eigen::Vector2f::Zero());
    }
}

TrailEntity::~TrailEntity()
{
    while (head) {
        auto next = std::move(head->next);
        head = std::move(next);
    }
    
}


void TrailEntity::Draw(WindowController& winCtrl) {
    
    Eigen::Vector2i winSize = winCtrl.getWindowSize();
    this->updatePosition(winSize.y(), winSize.x());
    BodyPart* current;
    current = this->head.get();
    while (current) {
        this->blit(winCtrl.getRenderer(), static_cast<int>(current->position.x()), static_cast<float>(current->position.y()),1);
        current = current->next.get();
    }
    blit(winCtrl.getRenderer(), 1);
    SDL_RenderPresent(winCtrl.getRenderer());
}
/*
Adds velocity to position. Wraps position to screen boundaries
*/
void TrailEntity::updatePosition(int screenHeight, int screenWidth) {
    position += velocity;

    position[0] = moduloHelper(position[0], static_cast<float>(screenWidth));
    position[1] = moduloHelper(position[1], static_cast<float>(screenHeight));
    
    head->position = position;
    BodyPart* current = head->next.get();
    Eigen::Vector2f posPrev = head->position;
    Eigen::Vector2f posNext;
    float dist =0;
    while (current) {

        posNext = current->position;
        dist = (posNext - posPrev).norm();
        current->position += (posPrev- posNext).normalized() *(tanh(dist - this->GetTextureSize().x) + 1.0);
        posPrev = current->position;
        current = current->next.get();
        
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
    grid= grid.Zero(cols,rows);
    
    std::cout << grid << std::endl;
    grid(3, 4) = 64;
    grid(1, 1) = -1;

}

void GridEntity::setGridCell(int x, int y, int value) {
    grid(x,y) = value;
    
}

void GridEntity::forAllCells(std::function<int(int)> func) {
    grid.unaryExpr(func);
}

void GridEntity::forAllCells(std::function<void(SDL_Texture* texture, int x, int y)>func) {
    grid = Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic>::NullaryExpr(rows,cols,[&grid=grid,&cellSize = cellSize, &func = func, &texture = texture](Eigen::Index i, Eigen::Index j){
        if (grid(i, j) > 0) {
            func(texture, i*cellSize, j*cellSize);
            return --grid(i,j);
        }
    });
}

void GridEntity::Draw(WindowController& winCtrl) {

}

bool GridEntity::IsComposite () const { return true;}