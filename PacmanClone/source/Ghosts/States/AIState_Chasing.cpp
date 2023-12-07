#include "PacmanCore.h"
#include "AIState_Chasing.h"

AIState_Chasing::AIState_Chasing(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Chasing::OnStateEnter()
{
}

void AIState_Chasing::OnStateRunning()
{
}

void AIState_Chasing::OnStateExit()
{
}
