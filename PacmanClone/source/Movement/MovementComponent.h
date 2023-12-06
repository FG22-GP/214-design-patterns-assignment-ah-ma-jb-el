#pragma once

#include "PacmanCore.h"

#include "Engine/World/Actors/ActorComponent.hpp"
#include "Data/Vectors/Vector2.hpp"

class GridLink;
class GridCell;

class MovementComponent : ActorComponent
{
    
public:
    void SetDirection(Directions direction);
    void SetLerpDuration(float duration);

protected:
    Directions currentDirection {};
    Directions newDirection {};

    void Tick(float DeltaTime) override;


private:
    float fTimeElapsed = 0;
    float fLerpDuration = 1;
    bool bWrapLerp = false;
    std::shared_ptr<GridCell> StartCell;
    std::shared_ptr<GridCell> TargetCell;

    void NextCell();
    void LerpMovement(float DeltaTime);
    Vector2 WrapLerp(Vector2 start, Vector2 target, float T);
    bool IsWrapLink(std::shared_ptr<GridLink>& link);
};
