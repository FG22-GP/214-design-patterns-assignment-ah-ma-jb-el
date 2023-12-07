#include "PacmanCore.h"
#include "AIState_Chasing.h"

#include "Ghosts/IGhost.h"

AIState_Chasing::AIState_Chasing(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Chasing::OnStateEnter()
{
}

void AIState_Chasing::OnStateRunning()
{
    Ghost->ChasePlayer();
}

void AIState_Chasing::OnStateExit()
{
}
