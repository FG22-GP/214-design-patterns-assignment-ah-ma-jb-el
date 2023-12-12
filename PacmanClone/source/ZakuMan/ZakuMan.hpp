#pragma once
#include "PacmanCore.h"

#include "Grid/GridCellContent.h"
#include "World/Actors/Actor.hpp"



class GridCellContent;
class MovementComponent;
class StateMachine_Component;

class ZakuMan : public Actor, public GridCellContent
{
public:
    ZakuMan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
    
    std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return SpriteComp; }
    std::shared_ptr<MovementComponent> GetMovementComponent() const { return MoveComp; }
    
private:
    std::shared_ptr<MovementComponent> MoveComp;
    std::shared_ptr<SpriteComponent> SpriteComp;
    
};
