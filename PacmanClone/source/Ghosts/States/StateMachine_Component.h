#pragma once
#include "World\Actors\ActorComponent.hpp"

class IAIState;
class AIState_Chasing;
class AIState_Frightened;
class AIState_Scatter;
class AIState_Dead;

class StateMachine_Component : public ActorComponent
{
public:
    StateMachine_Component(std::shared_ptr<Actor> ParentActor);
    std::shared_ptr<IAIState> CurrentState;

    void RunCurrentState() const;
    bool IsDead() const;

    void PushFrightened();
    void PushScatter();
    void PushChase();
    void PushDead();
    
protected:

    void Tick(float DeltaTime) override;
    
private:
    std::shared_ptr<AIState_Chasing> ChaseState;
    std::shared_ptr<AIState_Frightened> FrightenedState;
    std::shared_ptr<AIState_Scatter> ScatterState;
    std::shared_ptr<AIState_Dead> DeadState;

    void PushNewState(std::shared_ptr<IAIState> newState);
};
