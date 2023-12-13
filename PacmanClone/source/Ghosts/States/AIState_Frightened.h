#pragma once
#include "IAIState.h"

class AIState_Frightened : public IAIState
{
public:
    AIState_Frightened(const std::shared_ptr<IGhost>& ghost);
    void OnStateEnter() override;
    void OnStateRunning() override;
    void OnStateExit() override;
    void OnStateTick(float DeltaTime) override;

private:
    float fTimer = 0;
    float fFrightenedDuration = 10;
    
};
