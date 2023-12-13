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
    const std::shared_ptr<StateMachine_Component> machine = Ghost->GetStateMachineComponent();
    if (machine == nullptr) { return; }
    
    fTimer += DeltaTime;
    if (fTimer >= fFrightenedDuration)
    {
        if (machine->bScatter)
        {
            machine->PushScatter();
        }
        else
        {
            machine->PushChase();
        }
        
        fTimer = 0;
    }
}

void AIState_Frightened::OnZakuOverlap()
{
    const std::shared_ptr<StateMachine_Component> machine = Ghost->GetStateMachineComponent();
    if (machine == nullptr) { return; }

    machine->PushDead();
}
