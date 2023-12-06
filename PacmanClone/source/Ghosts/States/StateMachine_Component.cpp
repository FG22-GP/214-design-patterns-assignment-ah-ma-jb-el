#include "PacmanCore.h"
#include "StateMachine_Component.h"

#include "AIState_Chasing.h"
#include "AIState_Dead.h"
#include "AIState_Frightened.h"
#include "AIState_Scatter.h"

void StateMachine_Component::OnStart()
{
    ActorComponent::OnStart();

    std::shared_ptr<StateMachine_Component> thisMachine = shared_from_this();
    
    ChaseState = std::make_shared<AIState_Chasing>();
    ChaseState->SetMachine(thisMachine);
    FrightenedState = std::make_shared<AIState_Frightened>();
    FrightenedState->SetMachine(thisMachine);
    ScatterState = std::make_shared<AIState_Scatter>();
    ScatterState->SetMachine(thisMachine);
    DeadState = std::make_shared<AIState_Dead>();
    DeadState->SetMachine(thisMachine);

    CurrentState = ChaseState;
}

void StateMachine_Component::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    CurrentState->OnStateRunning();
}

void StateMachine_Component::PushNewState(std::shared_ptr<AIState_Base> newState)
{
    if (newState == nullptr || newState == CurrentState) { return; }
    
    CurrentState->OnStateExit();
    newState->OnStateEnter();
    CurrentState = newState;
}
