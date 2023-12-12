#include "PacmanCore.h"
#include "Pathfinding.h"

#include <queue>

#include "Grid/GridCell.h"
#include "Grid/GridLink.h"


Directions Pathfinding::GetDirection(std::shared_ptr<GridCell> currentCell, std::shared_ptr<GridCell> nextCell, Point2 targetCoord)
{
    if (currentCell == nullptr || nextCell == nullptr)
    {
        return None;
    }
    
    float lowestDistance = 999.f;
    int index {};
    for (int i = 0; i < nextCell->Links.size(); i++)
    {
        std::shared_ptr<GridCell> cell = nextCell->Links[i]->Target;
        if (!cell->bIsGhostWalkable || cell == currentCell) { continue; }
        
        const float newDistance = Calculate_Distance(cell, targetCoord);
        if (newDistance < lowestDistance)
        {
            lowestDistance = newDistance;
            index = i;
        }
    }

    Directions Dir = static_cast<Directions>(index);

    return Dir;
    
    // switch (index)
    // {
    // case Up:
    //     return Up;
    // case Down:
    //     return Down;
    // case Right:
    //     return Right;
    // case Left:
    //     return Left;
    // default:
    //     return Up;
    // }
    
}

float Pathfinding::Calculate_Distance(std::shared_ptr<GridCell> start, Point2 goal)
{
    const int startX = start->Coordinate.GetX();
    const int startY = start->Coordinate.GetY();
    const int goalX = goal.GetX();
    const int goalY = goal.GetX();

    const int x_sq = (startX - goalX) * (startX - goalX);
    const int y_sq = (startY - goalY) * (startY - goalY);

    const float sqrt = static_cast<float>(std::sqrt(x_sq + y_sq));

    return sqrt;
}
