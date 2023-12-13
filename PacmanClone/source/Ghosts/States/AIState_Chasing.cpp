#include "PacmanCore.h"
#include "AIState_Chasing.h"

#include "Ghosts/IGhost.h"
#include "Grid/GridCell.h"

AIState_Chasing::AIState_Chasing(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Chasing::OnStateEnter()
{
    
}

void AIState_Chasing::OnStateRunning()
{
    if (Ghost == nullptr) { return; }
    
    if (Ghost->GetCell()->bIsGhostWalkable && !Ghost->GetCell()->bIsPlayerWalkable)
    {
        Ghost->Scatter(Ghost->GetDeathCell());
    }
    else
    {
        Ghost->ChasePlayer();
    }    
}

void AIState_Chasing::OnStateExit()
{
}

void AIState_Chasing::OnStateTick(float DeltaTime)
{

}
