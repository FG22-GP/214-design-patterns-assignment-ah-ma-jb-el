#include "PacmanCore.h"
#include "Ghost_Erik.h"

#include "Grid/GridCellContent.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"


std::shared_ptr<GridCell> Ghost_Erik::GetTargetCell()
{
    std::shared_ptr<GridCell> ZakuCell = ZakuMan->GetCell();
    Directions ZakuDir; // = ZakuMan->GetMovementComponent()->currentDirection;  behöver en getter här

    return nullptr;
}
