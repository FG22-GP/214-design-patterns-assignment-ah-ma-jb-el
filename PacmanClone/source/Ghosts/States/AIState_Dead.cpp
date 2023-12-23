#include "PacmanCore.h"
#include "AIState_Dead.h"

#include "Ghosts/IGhost.h"
#include "Grid/GridCell.h"

AIState_Dead::AIState_Dead(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Dead::OnStateEnter()
{
    //change to "dead" sprite
    Ghost->GetSpriteComponent()->GoTo(2);
}

void AIState_Dead::OnStateRunning()
{
    if (Ghost == nullptr) { return; }

    if (Ghost->GetCell()->Coordinate == Ghost->GetDeathCell())
    {
        const std::shared_ptr<StateMachine_Component> machine = Ghost->GetStateMachineComponent();
        if (machine == nullptr) { return; }
        
        if (machine->bScatter)
        {
            machine->PushScatter(true);
        }
        else
        {
            machine->PushChase(true);
        }
    }
    else
    {
        Ghost->Scatter(Ghost->GetDeathCell());
    }
}

void AIState_Dead::OnStateExit()
{
    //change to default sprite
    Ghost->GetSpriteComponent()->GoTo(0);
}

void AIState_Dead::OnStateTick(float DeltaTime)
{
    
}

void AIState_Dead::OnZakuOverlap()
{
}
