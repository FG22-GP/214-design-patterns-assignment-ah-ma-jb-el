#include "PacmanCore.h"
#include "IGhost.h"

#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"
#include "Movement/Pathfinding.h"

IGhost::IGhost(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) : Actor(ParentWorld, StartTransform)
{
    StateMachineComp = AddComponent<StateMachine_Component>();
    MovementComp = AddComponent<MovementComponent>();

    EnterCellCallback = MovementComp->OnEnterNewCellEvent.AddListener([this]()
    {
        StateMachineComp->RunCurrentState();
    });
    MiddleOfCellCallback = MovementComp->OnCenterOfCellEvent.AddListener([this]()
    {
        this->SetDirection();
    });
    
    SpriteComp = AddComponent<SpriteComponent>();
}


void IGhost::ChasePlayer()
{
    if (MovementComp == nullptr) { return; }
    
    const Directions newDir = Pathfinding::GetDirection(MovementComp->GetCurrentCell(), MovementComp->GetTargetCell(), GetTargetCoord());
    // MovementComp->SetDirection(newDir);
    SavedDirection = newDir;
}

void IGhost::Flee()
{
    if (MovementComp == nullptr) { return; }

    std::vector<std::shared_ptr<GridCell>> cells;
    std::shared_ptr<GridCell> nextCell = MovementComp->GetTargetCell();
    for (int i = 0; i < nextCell->Links.size(); i++)
    {
        // välj random direction här på något sätt
        std::shared_ptr<GridCell> cell = nextCell->Links[i]->Target;
        if (!cell->bIsGhostWalkable || cell == MovementComp->GetCurrentCell()) { continue; }

        cells.push_back(cell);
    }

    if (cells.size() <= 0) { return; }
    
    int index = rand() % cells.size();

    Point2 dirVector = cells[index]->Coordinate - nextCell->Coordinate;

    if (dirVector == Point2::Up())
    {
        SavedDirection = Up;
        // MovementComp->SetDirection(Up);
    }
    else if (dirVector == Point2::Down())
    {
        SavedDirection = Down;
        // MovementComp->SetDirection(Down);
    }
    else if (dirVector == Point2::Right())
    {
        SavedDirection = Right;
        // MovementComp->SetDirection(Right);
    }
    else if (dirVector == Point2::Left())
    {
        SavedDirection = Left;
        // MovementComp->SetDirection(Left);
    }
    
}

void IGhost::Scatter(Point2 scatterCoords)
{
    if (MovementComp == nullptr) { return; }
    
    const Directions newDir = Pathfinding::GetDirection(MovementComp->GetCurrentCell(), MovementComp->GetTargetCell() ,scatterCoords);
    // MovementComp->SetDirection(newDir);
    SavedDirection = newDir;
}

void IGhost::SetDirection()
{
    if (MovementComp == nullptr) { return; }
    
    if (MovementComp->GetCurrentDirection() != SavedDirection)
    {
        MovementComp->SetDirection(SavedDirection);
    }
    
}

void IGhost::InitializeGhost(
    Point2 deathCell,
    Point2 scatterCoords,
    std::shared_ptr<::ZakuMan>& target)
{
    DeathCellCoords = deathCell;
    ScatterCellCoords = scatterCoords;
    ZakuMan = target;
    
}


#pragma region Getters
Point2 IGhost::GetScatterCoords()
{
    return ScatterCellCoords;
}

Point2 IGhost::GetDeathCell()
{
    return DeathCellCoords;
}

std::shared_ptr<ZakuMan> IGhost::GetTarget()
{
    return ZakuMan;
}

bool IGhost::IsDead() const
{
    if (StateMachineComp == nullptr) { return true; }

    return StateMachineComp->IsDead();
}

std::shared_ptr<MovementComponent> IGhost::GetMovementComponent()
{
    return MovementComp;
}

std::shared_ptr<StateMachine_Component> IGhost::GetStateMachineComponent()
{
    return StateMachineComp;
}

std::shared_ptr<SpriteComponent> IGhost::GetSpriteComponent()
{
    return SpriteComp;
}

Point2 IGhost::GetTargetCoord()
{
    return Point2{};
}
#pragma endregion 
