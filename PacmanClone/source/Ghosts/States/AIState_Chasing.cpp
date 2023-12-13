#include "PacmanCore.h"
#include "AIState_Chasing.h"

#include "Ghosts/IGhost.h"

AIState_Chasing::AIState_Chasing(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Chasing::OnStateEnter()
{
    fTimer = 0;
}

void AIState_Chasing::OnStateRunning()
{
    if (Ghost == nullptr) { return; }
    
    Ghost->ChasePlayer();
}

void AIState_Chasing::OnStateExit()
{
}

void AIState_Chasing::OnStateTick(float DeltaTime)
{
    fTimer += DeltaTime;
    if (fTimer >= fStateDuration)
    {
        Ghost->GetStateMachineComponent()->PushScatter();
    }
}
