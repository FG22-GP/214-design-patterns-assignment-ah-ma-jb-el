#pragma once
#include "World/Actors/Actor.hpp"
#include "Ghosts/States/StateMachine_Component.h"
#include "Grid/GridCellContent.h"
#include "World/Actors/SpriteSwitchComponent.hpp"

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
    void Scatter(Point2 scatterCoords);

    void SetDirection();
    void ChangeCell();

    void InitializeGhost(Point2 deathCell, Point2 scatterCoords, std::shared_ptr<ZakuMan>& target);

    Point2 GetScatterCoords();
    Point2 GetDeathCell();
    std::shared_ptr<ZakuMan> GetTarget();
    bool IsDead() const;

    std::shared_ptr<MovementComponent> GetMovementComponent();
    std::shared_ptr<StateMachine_Component> GetStateMachineComponent();
    std::shared_ptr<SpriteSwitchComponent> GetSpriteComponent();

protected:
    Point2 ScatterCellCoords;
    Point2 DeathCellCoords;
    Directions NextDirection = None;
    Directions CurrentDirection = None;

    Event<>::CallbackPtr EnterCellCallback;
    Event<>::CallbackPtr MiddleOfCellCallback;
    Event<std::shared_ptr<GridCellContent>>::CallbackPtr CellContentCallback;

    std::shared_ptr<GridCell> PreviousCell;
    std::shared_ptr<ZakuMan> ZakuMan;
    std::shared_ptr<StateMachine_Component> StateMachineComp;
    std::shared_ptr<MovementComponent> MovementComp;
    std::shared_ptr<SpriteSwitchComponent> SpriteComp;
    
    virtual Point2 GetTargetCoord();
};
