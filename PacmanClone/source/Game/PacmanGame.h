#pragma once

#include "PacmanCore.h"

#include "PacmanLevelInfoParser.h"
#include "Engine/Game/GameBase.h"
#include "World\World.hpp"


class ZakuMan;
class GameGrid;

class PacmanGame :
    public GameEngine::GameBase
{
public:
    std::shared_ptr<ZakuMan> SpawnPlayer() const;
    void SpawnGhosts(std::shared_ptr<ZakuMan> Player) const;
    virtual void Initialize() override;
    virtual void Run() override;
    virtual void Exit() override;
    virtual void HandleTick(float DeltaTime) override;
    virtual void HandleRendering() override;

protected:
    void LoadSprites();
    void LoadLevel();
    
    std::shared_ptr<World> GameWorld;
    std::shared_ptr<GameGrid> Grid;
    PacmanLevelInfo LevelInfo;

};

