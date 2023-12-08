#pragma once
#include "PacmanCore.h"
#include "World/Actors/Actor.hpp"



class GridCellContent;
class MovementComponent;
class StateMachine_Component;

class ZakuMan : public Actor
{
public:
    ZakuMan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
    
    std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return SpriteComp; }
    std::shared_ptr<MovementComponent> GetMovementComponent() const { return MoveComp; }
    std::shared_ptr<GridCellContent> GetCellContent() const { return CellContent; }
private:
    std::shared_ptr<MovementComponent> MoveComp;
    std::shared_ptr<SpriteComponent> SpriteComp;    
    std::shared_ptr<GridCellContent> CellContent;
};
