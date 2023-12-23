#include "PacmanCore.h"
#include "AIState_Scatter.h"

#include "Ghosts/IGhost.h"
#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"

AIState_Scatter::AIState_Scatter(const std::shared_ptr<IGhost>& ghost) : IAIState(ghost)
{
}

void AIState_Scatter::OnStateEnter()
{
    const Directions dir = Ghost->GetMovementComponent()->GetCurrentDirection();
    Ghost->GetMovementComponent()->SetDirection(Point2::GetOppositeDirection(dir));
}

void AIState_Scatter::OnStateRunning()
{
    if (Ghost == nullptr || Ghost->GetCell() == nullptr) { return; }

    if (Ghost->GetCell()->bIsGhostWalkable && !Ghost->GetCell()->bIsPlayerWalkable)
    {
        Ghost->GetOutOfGhostZone();
    }
    else
    {
        Ghost->Scatter(Ghost->GetScatterCoords());
    }
}

void AIState_Scatter::OnStateExit()
{
}

void AIState_Scatter::OnStateTick(float DeltaTime)
{

}

void AIState_Scatter::OnZakuOverlap()
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
