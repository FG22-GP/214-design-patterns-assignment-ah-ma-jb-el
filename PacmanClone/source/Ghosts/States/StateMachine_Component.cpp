#include "PacmanCore.h"
#include "StateMachine_Component.h"

#include "AIState_Chasing.h"
#include "AIState_Dead.h"
#include "AIState_Frightened.h"
#include "AIState_Scatter.h"

void StateMachine_Component::OnStart()
{
    ActorComponent::OnStart();
    
    
    ChaseState = std::make_shared<AIState_Chasing>();
    FrightenedState = std::make_shared<AIState_Frightened>();
    ScatterState = std::make_shared<AIState_Scatter>();
    DeadState = std::make_shared<AIState_Dead>();

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
