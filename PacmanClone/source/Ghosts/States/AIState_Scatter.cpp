#include "PacmanCore.h"
#include "AIState_Scatter.h"

#include "Ghosts/IGhost.h"

AIState_Scatter::AIState_Scatter(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Scatter::OnStateEnter()
{
}

void AIState_Scatter::OnStateRunning()
{
    Ghost->Scatter(nullptr);
}

void AIState_Scatter::OnStateExit()
{
}
