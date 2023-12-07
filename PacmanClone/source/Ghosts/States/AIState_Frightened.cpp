#include "PacmanCore.h"
#include "AIState_Frightened.h"

AIState_Frightened::AIState_Frightened(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Frightened::OnStateEnter()
{
}

void AIState_Frightened::OnStateRunning()
{
}

void AIState_Frightened::OnStateExit()
{
}
