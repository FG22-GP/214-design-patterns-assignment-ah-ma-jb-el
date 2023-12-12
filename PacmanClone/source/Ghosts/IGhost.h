#pragma once
#include "World/Actors/Actor.hpp"
#include "Ghosts/States/StateMachine_Component.h"
#include "Grid/GridCellContent.h"

class ZakuMan;
class SpriteComponent;
class GridCellContent;
class MovementComponent;
class StateMachine_Component;
class GridCell;
class Actor;

class IGhost : public Actor, public GridCellContent
{
public:
    IGhost(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
    void ChasePlayer();
    void Flee();
    void Scatter(std::shared_ptr<GridCell> scatterCell);

    std::shared_ptr<GridCell> GetScatterCell();
    std::shared_ptr<GridCell> GetDeathCell();
    std::shared_ptr<ZakuMan> GetTarget();

    std::shared_ptr<MovementComponent> GetMovementComponent();

protected:
    std::shared_ptr<GridCell> ScatterCell;
    std::shared_ptr<GridCell> DeathCell;
    
    std::shared_ptr<ZakuMan> ZakuMan;
    std::shared_ptr<StateMachine_Component> StateMachineComp;
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<SpriteComponent> SpriteComp;
    
    virtual Point2 GetTargetCoord();
};
