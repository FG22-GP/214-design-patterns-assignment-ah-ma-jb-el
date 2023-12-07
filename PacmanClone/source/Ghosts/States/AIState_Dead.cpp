#include "PacmanCore.h"
#include "AIState_Dead.h"

AIState_Dead::AIState_Dead(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Dead::OnStateEnter()
{
}

void AIState_Dead::OnStateRunning()
{
}

void AIState_Dead::OnStateExit()
{
}
