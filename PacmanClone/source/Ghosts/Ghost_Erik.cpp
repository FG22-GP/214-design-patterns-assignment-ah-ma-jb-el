#include "PacmanCore.h"
#include "Ghost_Erik.h"

#include "Grid/GameGrid.h"
#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"


std::shared_ptr<GridCell> Ghost_Erik::GetTargetCell()
{
    std::shared_ptr<GridCell> ZakuCell = ZakuMan->GetCell();
    Directions ZakuDir = Up; // = ZakuMan->GetMovementComponent()->currentDirection;  behöver en Getter här

    if (ZakuCell == nullptr) { return nullptr; }

    Point2 newCoord = ZakuCell->Coordinate
    + Point2::DirectionVector(ZakuDir)
    + Point2::DirectionVector(ZakuDir)
    + Point2::DirectionVector(ZakuDir)
    + Point2::DirectionVector(ZakuDir);

    
    std::shared_ptr<GridCell> target = ZakuCell->Grid->GetCellAt(newCoord);

    if (target != nullptr) { return target; }
    
    return nullptr;
}
