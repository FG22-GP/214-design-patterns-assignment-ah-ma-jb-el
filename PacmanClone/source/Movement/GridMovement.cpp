#include "PacmanCore.h"
#include "GridMovement.h"

#include "Engine/World/Actors/Actor.hpp"
#include "Grid/GridCell.h"
#include "Grid/GridLink.h"

void GridMovement::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    // NextCell(nullptr, DeltaTime);
}

void GridMovement::NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime)
{
    std::shared_ptr<GridCell> target = currentCell->Links[newDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        // window-pixel-coordinates, somehow?
        LerpMovement(Vector2(0,0), Vector2(1,1), DeltaTime);
        
        currentDirection = newDirection;
    }
    target = currentCell->Links[currentDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        // window-pixel-coordinates, somehow?
        LerpMovement(Vector2(0,0), Vector2(1,1), DeltaTime);
    }
}

void GridMovement::LerpMovement(Vector2 start, Vector2 target, float DeltaTime)
{
    if (fTimeElapsed < fLerpDuration)
    {
        fTimeElapsed += DeltaTime;

        if (fTimeElapsed > fLerpDuration / 2 - DeltaTime / 2 &&
            fTimeElapsed < fLerpDuration / 2 + DeltaTime / 2)
        {
            //event here: half way through lerp !!
        }

        Vector2 newPosition = LerpVector2(start, target, fTimeElapsed/fLerpDuration);
        Parent->ActorTransform.SetLocation(newPosition);
    }

    fTimeElapsed = 0;
}

Point2 GridMovement::LerpPoint2(Point2 p1, Point2 p2, float T)
{
    Point2 Result;
    Result.x = static_cast<int>((1 - T) * p1.x + T * p2.x);
    Result.y = static_cast<int>((1 - T) * p1.y + T * p2.y);
    return Result;
}

Vector2 GridMovement::LerpVector2(Vector2 v1, Vector2 v2, float T)
{
    Vector2 Result;
    Result.X = ((1 - T) * v1.X + T * v2.X);
    Result.Y = ((1 - T) * v1.Y + T * v2.Y);
    return Result;
}

void GridMovement::SetDirection(Directions direction)
{
    newDirection = direction;
}

void GridMovement::SetLerpDuration(float duration)
{
    fLerpDuration = duration;
}

