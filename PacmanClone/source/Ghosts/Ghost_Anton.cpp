#include "PacmanCore.h"
#include "Ghost_Anton.h"

#include "Grid/GridCellContent.h"
#include "ZakuMan/ZakuMan.hpp"

std::shared_ptr<GridCell> Ghost_Anton::GetTargetCell()
{
    return ZakuMan->GetCell();
}
