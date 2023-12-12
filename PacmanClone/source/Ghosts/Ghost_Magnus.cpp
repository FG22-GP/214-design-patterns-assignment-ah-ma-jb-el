#include "PacmanCore.h"
#include "Ghost_Magnus.h"

#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"
#include "Movement/Pathfinding.h"
#include "ZakuMan/ZakuMan.hpp"


Point2 Ghost_Magnus::GetTargetCoord()
{
    //initial null-checks
    if (MovementComp == nullptr || ZakuMan == nullptr) { return Point2{}; }
    
    const std::shared_ptr<GridCell> startCell = MovementComp->GetTargetCell();
    std::shared_ptr<GridCell> targetCell = ZakuMan->GetCell();

    //secondary null-checks
    if (startCell == nullptr || targetCell  == nullptr) { return Point2{}; }
    
    const float distance = Pathfinding::Calculate_Distance(startCell, targetCell->Coordinate);
    
    if (distance > 8)
    {
        return targetCell->Coordinate;
    }

    return ScatterCell->Coordinate;
}
