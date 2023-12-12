#include "PacmanCore.h"
#include "AIState_Scatter.h"

#include "Ghosts/IGhost.h"
#include "Movement/MovementComponent.h"

AIState_Scatter::AIState_Scatter(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Scatter::OnStateEnter()
{
    const Directions dir = Ghost->GetMovementComponent()->GetCurrentDirection();
    Ghost->GetMovementComponent()->SetDirection(DirectionHelpers::GetOppositeDirection(dir));
}

void AIState_Scatter::OnStateRunning()
{
    if (Ghost == nullptr) { return; }
    
    Ghost->Scatter(Ghost->GetScatterCell());
}

void AIState_Scatter::OnStateExit()
{
}
