#pragma once

#include "PacmanCore.h"

#include "World\Actors\ActorComponent.hpp"
#include "Data/Vectors/Vector2.hpp"
#include "Event/Event.h"

class GridLink;
class GridCell;

class MovementComponent : public ActorComponent
{
public:
    MovementComponent(std::shared_ptr<Actor> ParentActor) :
        ActorComponent(ParentActor)
    {
    }

    void SetDirection(Directions newDirection);

    void Init(std::shared_ptr<GridCell> startCell, Directions startDirection);

    std::shared_ptr<GridCell> GetTargetCell() { return TargetCell; }
    std::shared_ptr<GridCell> GetCurrentCell() { return CurrentCell; }
    Directions GetCurrentDirection() const { return MoveDirection; }
    void SetMoveSpeed(float speed) { fMoveSpeed = speed; }

    Event<> OnEnterNewCellEvent;
    Event<> OnCenterOfCellEvent;
    
protected:
    Directions MoveDirection = Directions::None;
    Directions SteeringDirection = Directions::Right;
    std::shared_ptr<GridCell> CurrentCell = nullptr;
    std::shared_ptr<GridLink> CurrentLink = nullptr;
    std::shared_ptr<GridCell> TargetCell = nullptr;
    float fMoveSpeed = 2;

    void Tick(float DeltaTime) override;
    virtual void Move(float DeltaTime);
    virtual bool TrySetNewTargetCell();
    void OnEnterNewCell(const std::shared_ptr<GridCell>& newCell);
    Vector2 WrapLerp(Vector2 start, Vector2 target, float T);
    bool IsWrapLink(std::shared_ptr<GridLink>& link);

};
