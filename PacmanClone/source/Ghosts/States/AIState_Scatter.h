#pragma once
#include "IAIState.h"

class AIState_Scatter : public IAIState
{
public:
    AIState_Scatter(const std::shared_ptr<IGhost>& ghost);
    void OnStateEnter() override;
    void OnStateRunning() override;
    void OnStateExit() override;
    void OnStateTick(float DeltaTime) override;
};
