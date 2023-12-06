#pragma once

class AIState_Base
{
public:
    virtual ~AIState_Base() = default;
    
    virtual void OnStateEnter() = 0;
    virtual void OnStateRunning() = 0;
    virtual void OnStateExit() = 0;
};
