#include "Entity.h"
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <iostream>

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

    auto push = [&head=head](Eigen::Vector2<int> pos) {
        head = std::unique_ptr<BodyPart>(new BodyPart{pos, std::move(head)});
    };

    for (int i = 0; i < length; i++) {
        push(Eigen::Vector2<int>::Zero());
    }
}

TrailEntity::~TrailEntity()
{
    while (head) {
        auto next = std::move(head->next);
        head = std::move(next);
    }
    
}

/*
Adds velocity to position. Wraps position to screen boundaries
*/
void TrailEntity::updatePosition(int screenHeight, int screenWidth) {
    position += velocity;

    position[0] = moduloHelper(position[0], screenWidth);
    position[1] = moduloHelper(position[1], screenHeight);
    
    head->position = position;
    BodyPart* current = head.get();
    Eigen::Vector2<int> posPrev = current->position;
    Eigen::Vector2<int> posNext = current->position;
    while (current->next) {
        current = current->next.get();
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