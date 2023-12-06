#pragma once
#include "AIState_Base.h"

class AIState_Scatter : public AIState_Base
{
public:
    void OnStateEnter() override;
    void OnStateRunning() override;
    void OnStateExit() override;
};
