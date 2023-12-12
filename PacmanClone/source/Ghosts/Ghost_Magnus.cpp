#include "PacmanCore.h"
#include "Ghost_Magnus.h"

#include "Movement/MovementComponent.h"
#include "Movement/Pathfinding.h"
#include "ZakuMan/ZakuMan.hpp"


std::shared_ptr<GridCell> Ghost_Magnus::GetTargetCell()
{
    const std::shared_ptr<GridCell> startCell = MovementComp->GetTargetCell();
    const std::shared_ptr<GridCell> targetCell = ZakuMan->GetCell();

    if (startCell == nullptr || targetCell  == nullptr)
    {
        return nullptr;
    }
    
    const float distance = Pathfinding::Calculate_Distance(startCell, targetCell);
    
    if (distance > 8)
    {
        return nullptr; // <- method here
    }

    return nullptr; // <- method here
}
