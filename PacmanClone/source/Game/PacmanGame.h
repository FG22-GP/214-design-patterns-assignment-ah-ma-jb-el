#pragma once

#include "PacmanCore.h"
#include "Engine/Game/GameBase.h"
#include "World\World.hpp"


class GameGrid;

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
    void LoadLevel();
    
    std::shared_ptr<World> GameWorld;
    std::shared_ptr<GameGrid> Grid;

    //TESTING
    //This is test code to show how to make textures, sprites, actors and sprite components.
    bool bUseTestFunctions;
    void TEST_Init(); 
    void TEST_Tick(float DeltaTime);
    std::shared_ptr<Actor> TestActor;
    std::string TestPath = 
        "Sprites/TestSprite.png";

};

