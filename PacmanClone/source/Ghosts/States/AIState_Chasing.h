#pragma once
#include "IAIState.h"

class AIState_Chasing : public IAIState
{
public:
    AIState_Chasing(const std::shared_ptr<IGhost>& ghost);
    void OnStateEnter() override;
    void OnStateRunning() override;
    void OnStateExit() override;
};
