#pragma once

class AIState_Base
{
public:
    virtual void OnStateEnter() = 0;
    virtual void OnStateRunning() = 0;
    virtual void OnStateExit() = 0;
};
