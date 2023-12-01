#include "PacmanCore.h"
#include "GridMovement.h"
#include "Grid/GridCell.h"
#include "Grid/GridLink.h"

std::shared_ptr<GridCell> GridMovement::NextCell(std::shared_ptr<GridCell> currentCell)
{
    std::shared_ptr<GridCell> target = currentCell->Links[newDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        currentDirection = newDirection;
        return target; 
    }
    target = currentCell->Links[currentDirection]->Target;
    if (target != nullptr && target->bIsWalkable)
    {
        return target; 
    }
    return currentCell;
}

void GridMovement::SetDirection(Directions direction)
{
    newDirection = direction;
}
