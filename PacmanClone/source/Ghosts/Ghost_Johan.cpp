#include "PacmanCore.h"
#include "Ghost_Johan.h"


std::shared_ptr<GridCell> Ghost_Johan::GetTargetCell()
{
    return IGhost::GetTargetCell();
}
