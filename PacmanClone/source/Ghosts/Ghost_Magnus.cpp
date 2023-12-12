#include "PacmanCore.h"
#include "Ghost_Magnus.h"


std::shared_ptr<GridCell> Ghost_Magnus::GetTargetCell()
{
    return IGhost::GetTargetCell();
}
