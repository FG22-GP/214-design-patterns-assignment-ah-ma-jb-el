﻿#pragma once

#include "PacmanCore.h"

#include "World\Actors\ActorComponent.hpp"
#include "Data/Vectors/Vector2.hpp"

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

    void SetLerpDuration(float duration) { fLerpDuration = duration; }
    void Init(std::shared_ptr<GridCell> startCell);

    std::shared_ptr<GridCell> GetTargetCell() { return TargetCell; }
    std::shared_ptr<GridCell> GetCurrentCell() { return StartCell; }
    Directions GetCurrentDirection() const { return currentDirection; }

protected:
    Directions currentDirection = Directions::None;
    Directions cachedDirection = Directions::None;

    void Tick(float DeltaTime) override;

private:
    float fTimeElapsed = 0;
    float fLerpDuration = 1;
    bool bWrapLerp = false;
    std::shared_ptr<GridCell> StartCell = nullptr;
    std::shared_ptr<GridCell> TargetCell = nullptr;

    void TrySetNewTargetCell();
    void Move(float DeltaTime);
    Vector2 WrapLerp(Vector2 start, Vector2 target, float T);
    bool IsWrapLink(std::shared_ptr<GridLink>& link);
};
