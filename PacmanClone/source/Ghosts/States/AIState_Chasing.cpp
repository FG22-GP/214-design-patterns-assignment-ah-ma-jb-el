#include "PacmanCore.h"
#include "AIState_Chasing.h"

#include "Ghosts/IGhost.h"
#include "Grid/GridCell.h"

AIState_Chasing::AIState_Chasing(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Chasing::OnStateEnter()
{
    
}

void AIState_Chasing::OnStateRunning()
{
    if (Ghost == nullptr) { return; }
    
    if (Ghost->GetCell()->bIsGhostWalkable && !Ghost->GetCell()->bIsPlayerWalkable)
    {
        Ghost->Scatter(Ghost->GetDeathCell());
    }
    else
    {
        Ghost->ChasePlayer();
    }    
}

void AIState_Chasing::OnStateExit()
{
}

void AIState_Chasing::OnStateTick(float DeltaTime)
{

}

void AIState_Chasing::OnZakuOverlap()
{
    std::cout << "Zaku is eaten; you should see You Lose text now" << std::endl;
    auto World = Ghost->GetWorld();
    if (World == nullptr) return;

    //Stop game and show lose screen
    World->bShouldTickActors = false;
    std::shared_ptr<Actor> WinSplash = World->CreateActor<Actor>();
    WinSplash->ActorTransform.SetLocation(Vector2(14, 16));
    WinSplash->ActorTransform.SetScale(Vector2(8, 8));
    auto spriteComp = WinSplash->AddComponent<SpriteComponent>();
    auto sprite = AssetLoader::GetSprite("Lost");
    spriteComp->Initialize(sprite);
}
