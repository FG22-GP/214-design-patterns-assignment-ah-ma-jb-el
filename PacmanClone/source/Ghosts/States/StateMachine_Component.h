#pragma once
#include "World\Actors\ActorComponent.hpp"

class AIState_Base;
class AIState_Chasing;
class AIState_Frightened;
class AIState_Scatter;
class AIState_Dead;

class StateMachine_Component : public ActorComponent, public std::enable_shared_from_this<StateMachine_Component>
{
public:
    StateMachine_Component();
    
    std::shared_ptr<AIState_Base> CurrentState;

    void PushNewState(std::shared_ptr<AIState_Base> newState);
    
protected:
    void OnStart() override;
    void Tick(float DeltaTime) override;
    
private:
    std::shared_ptr<AIState_Chasing> ChaseState;
    std::shared_ptr<AIState_Frightened> FrightenedState;
    std::shared_ptr<AIState_Scatter> ScatterState;
    std::shared_ptr<AIState_Dead> DeadState;
};
