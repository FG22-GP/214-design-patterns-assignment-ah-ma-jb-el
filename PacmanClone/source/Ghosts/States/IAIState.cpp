#include "PacmanCore.h"
#include "IAIState.h"

IAIState::IAIState(const std::shared_ptr<IGhost>& ghost)
{
    Ghost = ghost;
}

