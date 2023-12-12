#include "PacmanCore.h"
#include "AIState_Dead.h"

#include "Ghosts/IGhost.h"

AIState_Dead::AIState_Dead(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Dead::OnStateEnter()
{
    //change sprite to only eyes
}

void AIState_Dead::OnStateRunning()
{
    if (Ghost == nullptr) { return; }
    
    Ghost->Scatter(Ghost->GetDeathCell());
}

void AIState_Dead::OnStateExit()
{
    //change sprite back to default
}
