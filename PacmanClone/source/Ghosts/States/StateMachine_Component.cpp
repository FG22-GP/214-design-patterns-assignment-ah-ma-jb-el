#include "PacmanCore.h"
#include "StateMachine_Component.h"
#include "World/Actors/Actor.hpp"
#include "Ghosts/IGhost.h"
#include "AIState_Chasing.h"
#include "AIState_Dead.h"
#include "AIState_Frightened.h"
#include "AIState_Scatter.h"
#include "Event/EventBroker.h"
#include "ZakuMan/ZakuMan.hpp"

StateMachine_Component::StateMachine_Component(std::shared_ptr<Actor> ParentActor) : ActorComponent(ParentActor)
{
    std::shared_ptr<IGhost> ghost = std::dynamic_pointer_cast<IGhost>(Parent);

    if (ghost != nullptr)
    {
        ChaseState = std::make_shared<AIState_Chasing>(ghost);
        FrightenedState = std::make_shared<AIState_Frightened>(ghost);
        ScatterState = std::make_shared<AIState_Scatter>(ghost);
        DeadState = std::make_shared<AIState_Dead>(ghost);

        EventCallback = EventBroker::OnCookieEaten.AddListener([this]()
        {
            this->PushFrightened();
        });
        
        CurrentState = ScatterState;
    }
}

StateMachine_Component::~StateMachine_Component()
{
    EventBroker::OnCookieEaten.RemoveListener(EventCallback);
}

void StateMachine_Component::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    CurrentState->OnStateTick(DeltaTime);
    ScatterChaseTimer(DeltaTime);

}

void StateMachine_Component::RunCurrentState() const
{
    if (CurrentState != nullptr)
    {
        CurrentState->OnStateRunning();
    }
}

void StateMachine_Component::CheckForZaku()
{
    std::shared_ptr<IGhost> ghost = std::static_pointer_cast<IGhost>(Parent);
    if (ghost == nullptr) { return; }

    if (ghost->GetCell() == ghost->GetTarget()->GetCell())
    {
        CurrentState->OnZakuOverlap();
    }
}

void StateMachine_Component::ScatterChaseTimer(float DeltaTime)
{
    fTimer += DeltaTime;
    if (bScatter && fTimer >= fScatterDuration)
    {
        if (CurrentState != FrightenedState)
        {
            PushChase();
        }
        
        iScatterIncrement++;
        if (iScatterIncrement >= 2)
        {
            fScatterDuration = 5.f;
        }
        
        bScatter = false;
        fTimer = 0;
    }
    
    if (!bScatter && fTimer >= 20)
    {
        if (CurrentState != FrightenedState)
        {
            PushScatter();
        }

        if (iScatterIncrement < 4)
        {
            bScatter = true;
        }
        
        fTimer = 0;
    }
}

void StateMachine_Component::PushNewState(std::shared_ptr<IAIState> newState)
{
    if (newState == nullptr || newState == CurrentState) { return; }
    
    CurrentState->OnStateExit();
    newState->OnStateEnter();
    CurrentState = newState;
}

bool StateMachine_Component::IsDead() const
{
    return CurrentState == DeadState;
}

void StateMachine_Component::PushFrightened(bool bOverrideDead)
{
    if (!IsDead() || bOverrideDead)
    {
        PushNewState(FrightenedState);
    }
}

void StateMachine_Component::PushScatter(bool bOverrideDead)
{
    if (!IsDead() || bOverrideDead)
    {
        PushNewState(ScatterState);
    }
}

void StateMachine_Component::PushChase(bool bOverrideDead)
{
    if (!IsDead() || bOverrideDead)
    {
        PushNewState(ChaseState);
    }
}

void StateMachine_Component::PushDead()
{
    PushNewState(DeadState);
}
