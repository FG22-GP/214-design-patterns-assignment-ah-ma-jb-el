#include "PacmanCore.h"
#include "Ghost_Anton.h"

#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "ZakuMan/ZakuMan.hpp"

Point2 Ghost_Anton::GetTargetCoord()
{
    //initial null-checks
    if (ZakuMan == nullptr || ZakuMan->GetCell() == nullptr)
        { return Point2{}; }
    
    return ZakuMan->GetCell()->Coordinate;
}
