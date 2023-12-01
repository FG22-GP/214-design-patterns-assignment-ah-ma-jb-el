#include "PacmanCore.h"
#include "GridMovement.h"
#include "Grid/GridCell.h"
#include "Grid/GridLink.h"

void GridMovement::NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime)
{
    std::shared_ptr<GridCell> target = currentCell->Links[newDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        currentDirection = newDirection;
        // std::lerp();
    }
    target = currentCell->Links[currentDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        // std::lerp();
    }
}

void GridMovement::SetDirection(Directions direction)
{
    newDirection = direction;
}
