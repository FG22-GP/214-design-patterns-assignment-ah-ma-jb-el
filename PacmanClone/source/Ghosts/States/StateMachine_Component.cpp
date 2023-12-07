#include "PacmanCore.h"
#include "StateMachine_Component.h"
#include "World/Actors/Actor.hpp"
#include "Ghosts/IGhost.h"
#include "AIState_Chasing.h"
#include "AIState_Dead.h"
#include "AIState_Frightened.h"
#include "AIState_Scatter.h"



void StateMachine_Component::OnStart()
{
    ActorComponent::OnStart();

    std::shared_ptr<IGhost> ghost = std::dynamic_pointer_cast<IGhost>(Parent);

    if (ghost != nullptr)
    {
        ChaseState = std::make_shared<AIState_Chasing>(ghost);
        FrightenedState = std::make_shared<AIState_Frightened>(ghost);
        ScatterState = std::make_shared<AIState_Scatter>(ghost);
        DeadState = std::make_shared<AIState_Dead>(ghost);
    }
    
    CurrentState = ChaseState;
}

void StateMachine_Component::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    CurrentState->OnStateRunning();
}

void StateMachine_Component::PushNewState(std::shared_ptr<IAIState> newState)
{
    if (newState == nullptr || newState == CurrentState) { return; }
    
    CurrentState->OnStateExit();
    newState->OnStateEnter();
    CurrentState = newState;
}
