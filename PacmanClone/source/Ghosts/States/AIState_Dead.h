#pragma once
#include "IAIState.h"

class AIState_Dead : public IAIState
{
public:
    AIState_Dead(const std::shared_ptr<IGhost>& ghost);
    void OnStateEnter() override;
    void OnStateRunning() override;
    void OnStateExit() override;
    void OnStateTick(float DeltaTime) override;
    void OnZakuOverlap() override;
};
