#pragma once

#include "PacmanCore.h"

#include "World\Actors\ActorComponent.hpp"
#include "Data/Vectors/Vector2.hpp"

class GridLink;
class GridCell;

class MovementComponent : public ActorComponent
{
    
public:
    MovementComponent(std::shared_ptr<Actor> ParentActor) : 
        ActorComponent(ParentActor) {}
    
    void SetDirection(Directions direction);
    void SetLerpDuration(float duration);

    std::shared_ptr<GridCell> GetTargetCell();
    std::shared_ptr<GridCell> GetCurrentCell();

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
