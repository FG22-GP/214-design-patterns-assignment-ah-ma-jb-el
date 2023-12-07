#pragma once

#include "PacmanCore.h"
#include "Engine/Game/GameBase.h"
#include "World\World.hpp"


class PacmanGame :
    public GameEngine::GameBase
{
public:
    virtual void Initialize() override;
    virtual void Run() override;
    virtual void Exit() override;
    virtual void HandleTick(float DeltaTime) override;
    virtual void HandleRendering() override;

protected:
    std::unique_ptr<World> GameWorld;
};

