#pragma once

class IGhost;
class StateMachine_Component;

class IAIState
{
public:
    explicit IAIState(const std::shared_ptr<IGhost>& ghost);
    virtual ~IAIState() = default;
    
    virtual void OnStateEnter() = 0;
    virtual void OnStateRunning() = 0;
    virtual void OnStateExit() = 0;

    void SetMachine(std::shared_ptr<StateMachine_Component> machine);

protected:
    std::shared_ptr<IGhost> Ghost;
};
