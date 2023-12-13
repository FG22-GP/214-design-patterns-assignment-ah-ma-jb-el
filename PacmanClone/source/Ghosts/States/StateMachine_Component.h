#pragma once
#include "World\Actors\ActorComponent.hpp"
#include "Event/Event.h"

class IAIState;
class AIState_Chasing;
class AIState_Frightened;
class AIState_Scatter;
class AIState_Dead;

class StateMachine_Component : public ActorComponent
{
public:
    StateMachine_Component(std::shared_ptr<Actor> ParentActor);
    ~StateMachine_Component();

    std::shared_ptr<IAIState> CurrentState;

    bool bScatter = true;

    void RunCurrentState() const;
    bool IsDead() const;

    void PushFrightened(bool bOverrideDead = false);
    void PushScatter(bool bOverrideDead = false);
    void PushChase(bool bOverrideDead = false);
    void PushDead();
    
protected:

    Event<>::CallbackPtr EventCallback;
    void Tick(float DeltaTime) override;
    
private:
    std::shared_ptr<AIState_Chasing> ChaseState;
    std::shared_ptr<AIState_Frightened> FrightenedState;
    std::shared_ptr<AIState_Scatter> ScatterState;
    std::shared_ptr<AIState_Dead> DeadState;


    float fTimer = 0;
    float fScatterDuration = 7.f;
    int iScatterIncrement = 0;

    void ScatterChaseTimer(float DeltaTime);
    void PushNewState(std::shared_ptr<IAIState> newState);
};
