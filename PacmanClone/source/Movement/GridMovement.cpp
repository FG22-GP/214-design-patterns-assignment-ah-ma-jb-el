#include "PacmanCore.h"
#include "GridMovement.h"

#include "Grid/GridCell.h"
#include "Grid/GridLink.h"



void GridMovement::NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime)
{
    std::shared_ptr<GridCell> target = currentCell->Links[newDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        // window-pixel-coordinates, somehow?
        LerpMovement(Point2(0,0), Point2(1,1), DeltaTime);
        
        currentDirection = newDirection;
    }
    target = currentCell->Links[currentDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        // window-pixel-coordinates, somehow?
        LerpMovement(Point2(0,0), Point2(1,1), DeltaTime);
    }
}

Point2 GridMovement::LerpPoint2(Point2 p1, Point2 p2, float T)
{
    Point2 Result;
    Result.x = static_cast<int>((1 - T) * p1.x + T * p2.x);
    Result.y = static_cast<int>((1 - T) * p1.y + T * p2.y);
    return Result;
}

Point2 GridMovement::LerpMovement(Point2 start, Point2 target, float DeltaTime)
{
    if (fTimeElapsed < fLerpDuration)
    {
        fTimeElapsed += DeltaTime;

        if (fTimeElapsed > fLerpDuration / 2 - DeltaTime / 2 &&
            fTimeElapsed < fLerpDuration / 2 + DeltaTime / 2)
        {
            //event here: half way through lerp !!
        }
        
        return LerpPoint2(start, target, fTimeElapsed/fLerpDuration);
    }

    fTimeElapsed = 0;
    return target;   
}

void GridMovement::SetDirection(Directions direction)
{
    newDirection = direction;
}

void GridMovement::SetLerpDuration(float duration)
{
    fLerpDuration = duration;
}

