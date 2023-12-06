#pragma once

#include "PacmanCore.h"
#include "Engine/Game/GameBase.h"

class PacmanGame :
    public GameEngine::GameBase
{
public:
    virtual void Initialize() override;
    virtual void Run() override;
    virtual void Exit() override;
};

