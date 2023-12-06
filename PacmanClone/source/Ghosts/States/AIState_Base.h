#pragma once

class StateMachine_Component;

class AIState_Base
{
public:
    virtual ~AIState_Base() = default;
    
    virtual void OnStateEnter() = 0;
    virtual void OnStateRunning() = 0;
    virtual void OnStateExit() = 0;

    void SetMachine(std::shared_ptr<StateMachine_Component> machine);

protected:
    std::shared_ptr<StateMachine_Component> StateMachine;
};
