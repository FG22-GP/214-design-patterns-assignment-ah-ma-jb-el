#include "PacmanCore.h"
#include "AIState_Frightened.h"

#include "Ghosts/IGhost.h"

AIState_Frightened::AIState_Frightened(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Frightened::OnStateEnter()
{
    fTimer = 0;
    //change sprite to scared ghost
}

void AIState_Frightened::OnStateRunning()
{
    if (Ghost == nullptr) { return; }
    
    Ghost->Flee();
}

void AIState_Frightened::OnStateExit()
{
    //change sprite back to default
}

void AIState_Frightened::OnStateTick(float DeltaTime)
{
    fTimer += DeltaTime;
    if (fTimer >= fStateDuration)
    {
        Ghost->GetStateMachineComponent()->PushChase();
    }
}
