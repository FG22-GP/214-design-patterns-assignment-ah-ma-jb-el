#include "PacmanCore.h"
#include "Ghost_Erik.h"

#include "Grid/GameGrid.h"
#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"


Point2 Ghost_Erik::GetTargetCoord()
{
    //initial null-checks
    if (ZakuMan == nullptr || ZakuMan->GetCell() == nullptr || ZakuMan->GetMovementComponent() == nullptr)
        { return Point2{}; }
    
    std::shared_ptr<GridCell> ZakuCell = ZakuMan->GetCell();
    Directions ZakuDir = ZakuMan->GetMovementComponent()->GetCurrentDirection();
    
    if (ZakuDir == None) { return Point2{}; }

    Point2 newCoord = DirectionHelpers::GetPoint2InDirection(ZakuCell->Coordinate, ZakuDir, 4);
    return newCoord;
}
