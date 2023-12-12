#include "PacmanCore.h"
#include "IGhost.h"

#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"
#include "Movement/Pathfinding.h"

IGhost::IGhost(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) : Actor(ParentWorld, StartTransform)
{
    StateMachineComp = AddComponent<StateMachine_Component>();
    MovementComp = AddComponent<MovementComponent>();
    SpriteComp = AddComponent<SpriteComponent>();
}


void IGhost::ChasePlayer()
{
    const Directions newDir = Pathfinding::GetDirection(MovementComp->GetCurrentCell(), MovementComp->GetTargetCell(), GetTargetCoord());
    MovementComp->SetDirection(newDir);
}

void IGhost::Flee()
{
    std::shared_ptr<GridCell> nextCell = MovementComp->GetTargetCell();
    for (int i = 0; i < nextCell->Links.size(); i++)
    {
        // välj random direction här på något sätt
        std::shared_ptr<GridCell> cell = nextCell->Links[i]->Target;
        if (!cell->bIsGhostWalkable) { continue; }
        
    }
}

void IGhost::Scatter(std::shared_ptr<GridCell> scatterCell)
{
    const Directions newDir = Pathfinding::GetDirection(MovementComp->GetCurrentCell(), MovementComp->GetTargetCell() ,scatterCell->Coordinate);
    MovementComp->SetDirection(newDir);
}

#pragma region Getters
std::shared_ptr<GridCell> IGhost::GetScatterCell()
{
    return ScatterCell;
}

std::shared_ptr<GridCell> IGhost::GetDeathCell()
{
    return DeathCell;
}

std::shared_ptr<ZakuMan> IGhost::GetTarget()
{
    return ZakuMan;
}

std::shared_ptr<MovementComponent> IGhost::GetMovementComponent()
{
    return MovementComp;
}

Point2 IGhost::GetTargetCoord()
{
    return Point2{};
}
#pragma endregion 
