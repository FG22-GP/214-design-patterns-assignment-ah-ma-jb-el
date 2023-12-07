#pragma once
#include "World/Actors/Actor.hpp"

class GridCellContent;
class MovementComponent;
class StateMachine_Component;

class ZakuMan : public Actor
{
public:
    ZakuMan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);


    std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return SpriteComp; }
    
private:
    std::shared_ptr<MovementComponent> MoveComp;
    std::shared_ptr<SpriteComponent> SpriteComp;    
    std::shared_ptr<GridCellContent> CellContent;
};
