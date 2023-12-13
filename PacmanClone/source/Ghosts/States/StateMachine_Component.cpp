#include "PacmanCore.h"
#include "StateMachine_Component.h"
#include "World/Actors/Actor.hpp"
#include "Ghosts/IGhost.h"
#include "AIState_Chasing.h"
#include "AIState_Dead.h"
#include "AIState_Frightened.h"
#include "AIState_Scatter.h"

StateMachine_Component::StateMachine_Component(std::shared_ptr<Actor> ParentActor) : ActorComponent(ParentActor)
{
    std::shared_ptr<IGhost> ghost = std::dynamic_pointer_cast<IGhost>(Parent);

    if (ghost != nullptr)
    {
        ChaseState = std::make_shared<AIState_Chasing>(ghost);
        ChaseState->fStateDuration = 20.f;
        FrightenedState = std::make_shared<AIState_Frightened>(ghost);
        FrightenedState->fStateDuration = 10.f;
        ScatterState = std::make_shared<AIState_Scatter>(ghost);
        ChaseState->fStateDuration = 5.f;
        DeadState = std::make_shared<AIState_Dead>(ghost);
        
        CurrentState = ScatterState;
    }
}

void StateMachine_Component::RunCurrentState() const
{
    if (CurrentState != nullptr)
    {
        CurrentState->OnStateRunning();
    }
}

bool StateMachine_Component::IsDead() const
{
    return CurrentState == DeadState;
}

void StateMachine_Component::PushFrightened()
{
    PushNewState(FrightenedState);
}

void StateMachine_Component::PushScatter()
{
    PushNewState(ScatterState);
}

void StateMachine_Component::PushChase()
{
    PushNewState(ChaseState);
}

void StateMachine_Component::PushDead()
{
    PushNewState(DeadState);
}

void StateMachine_Component::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    if (CurrentState != nullptr)
    {
        CurrentState->OnStateRunning(); // should be changed to on state tick when events are in place
    }
}


void StateMachine_Component::PushNewState(std::shared_ptr<IAIState> newState)
{
    if (newState == nullptr || newState == CurrentState) { return; }
    
    CurrentState->OnStateExit();
    newState->OnStateEnter();
    CurrentState = newState;
}
