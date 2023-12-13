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

    void Init(std::shared_ptr<GridCell> startCell, bool inIsPlayer = false);

    std::shared_ptr<GridCell> GetTargetCell() { return TargetCell; }
    std::shared_ptr<GridCell> GetCurrentCell() { return CurrentCell; }
    Directions GetCurrentDirection() const { return MoveDirection; }
    void SetMoveSpeed(float speed) { fMoveSpeed = speed; }

    Event<> OnEnterNewCellEvent;
    Event<> OnCenterOfCellEvent;
    
protected:
    Directions MoveDirection = Directions::None;
    Directions SteeringDirection = Directions::Right;

    void Tick(float DeltaTime) override;

private:
    bool bIsPlayer = false;
    float fMoveSpeed = 2;
    std::shared_ptr<GridCell> CurrentCell = nullptr;
    std::shared_ptr<GridCell> TargetCell = nullptr;

    bool TrySetNewTargetCell();
    void Move(float DeltaTime);
    Vector2 WrapLerp(Vector2 start, Vector2 target, float T);
    bool IsWrapLink(std::shared_ptr<GridLink>& link);
    void OnEnterNewCell(const std::shared_ptr<GridCell>& newCell);
};
