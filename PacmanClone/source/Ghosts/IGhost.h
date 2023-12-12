#pragma once
#include "World/Actors/Actor.hpp"

class ZakuMan;
class SpriteComponent;
class GridCellContent;
class MovementComponent;
class StateMachine_Component;
class GridCell;
class Actor;

class IGhost : public Actor
{
public:
    IGhost(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
    virtual void ChasePlayer();
    void Flee();
    void Scatter(std::shared_ptr<GridCell> scatterCell);

    std::shared_ptr<GridCell> GetScatterCell();
    std::shared_ptr<GridCell> GetDeathCell();
    std::shared_ptr<ZakuMan> GetTarget();

protected:
    std::shared_ptr<GridCell> ScatterCell;
    std::shared_ptr<GridCell> DeathCell;
    
    std::shared_ptr<ZakuMan> PacMan;
    std::shared_ptr<StateMachine_Component> StateMachineComp;
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<GridCellContent> CellContentComp;
    std::shared_ptr<SpriteComponent> SpriteComp;
};
