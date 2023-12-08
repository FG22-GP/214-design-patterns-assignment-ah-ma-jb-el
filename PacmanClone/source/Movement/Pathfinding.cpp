#include "PacmanCore.h"
#include "Pathfinding.h"

#include <queue>

#include "Grid/GridCell.h"
#include "Grid/GridLink.h"


Point2 Pathfinding::Chase_GetDirection(std::shared_ptr<GridCell> nextCell, std::shared_ptr<GridCell> targetCell)
{
    float lowestDistance = 999.f;
    int index {};
    for (int i = 0; i < nextCell->Links.size(); i++)
    {
        std::shared_ptr<GridCell> cell = nextCell->Links[i]->Target;
        if (!cell->bIsGhostWalkable) { continue; }
        
        const float newDistance = Calculate_Distance(cell, targetCell);
        if (newDistance < lowestDistance)
        {
            lowestDistance = newDistance;
            index = i;
        }
    }

    switch (index)
    {
    case Up:
        return Point2::Up();
    case Down:
        return Point2::Down();
    case Right:
        return Point2::Right();
    case Left:
        return Point2::Left();
    default:
        return Point2{};
    }
    
}

float Pathfinding::Calculate_Distance(std::shared_ptr<GridCell> start, std::shared_ptr<GridCell> goal)
{
    int startX = start->Coordinate.GetX();
    int startY = start->Coordinate.GetY();
    int goalX = goal->Coordinate.GetX();
    int goalY = goal->Coordinate.GetX();

    int x_sq = (startX - goalX) * (startX - goalX);
    int y_sq = (startY - goalY) * (startY - goalY);

    float sqrt = std::sqrt(x_sq + y_sq);

    return sqrt;
}
