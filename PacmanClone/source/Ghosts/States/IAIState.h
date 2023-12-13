#pragma once

class IGhost;
class StateMachine_Component;

class IAIState
{
public:
    explicit IAIState(const std::shared_ptr<IGhost>& ghost);
    virtual ~IAIState() = default;
    
    float fStateDuration = 5;

    virtual void OnStateEnter() = 0;
    virtual void OnStateRunning() = 0;
    virtual void OnStateExit() = 0;
    virtual void OnStateTick(float DeltaTime) = 0;

protected:
    float fTimer = 0;
    std::shared_ptr<IGhost> Ghost;
};
