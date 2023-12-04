#pragma once

#include "PacmanCore.h"

#include "Engine/World/Actors/ActorComponent.hpp"
#include "Data/Vectors/Vector2.hpp"

class GridCell;

class GridMovement : ActorComponent
{
    
public:
    void NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime);
    
    void SetDirection(Directions direction);
    void SetLerpDuration(float duration);

protected:
    Directions currentDirection {};
    Directions newDirection {};

    void Tick(float DeltaTime) override;


private:
    float fTimeElapsed = 0;
    float fLerpDuration = 1;

    void LerpMovement(Vector2 start, Vector2 target, float DeltaTime);

    Point2 LerpPoint2(Point2 p1, Point2 p2, float T);
    Vector2 LerpVector2(Vector2 v1, Vector2 v2, float T);
};
