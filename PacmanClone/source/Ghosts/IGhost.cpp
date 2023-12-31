#include "PacmanCore.h"
#include "IGhost.h"

#include "Grid/GridCell.h"
#include "Movement/GhostMovementComponent.h"
#include "Movement/Pathfinding.h"

IGhost::IGhost(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) : Actor(ParentWorld, StartTransform)
{
    StateMachineComp = AddComponent<StateMachine_Component>();
    MovementComp = AddComponent<GhostMovementComponent>();

    EnterCellCallback = MovementComp->OnEnterNewCellEvent.AddListener([this]()
    {
        StateMachineComp->RunCurrentState();
        StateMachineComp->CheckForZaku();

        this->ChangeCell();
    });
    MiddleOfCellCallback = MovementComp->OnCenterOfCellEvent.AddListener([this]()
    {
        this->SetDirection();
    });
    
    SpriteComp = AddComponent<SpriteSwitchComponent>();
}


void IGhost::ChasePlayer()
{
    if (MovementComp == nullptr) { return; }
    
    const Directions newDir = Pathfinding::GetDirection(MovementComp->GetCurrentCell(), MovementComp->GetTargetCell(), GetTargetCoord());
    // MovementComp->SetDirection(newDir);
    NextDirection = newDir;
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
        NextDirection = Up;
        // MovementComp->SetDirection(Up);
    }
    else if (dirVector == Point2::Down())
    {
        NextDirection = Down;
        // MovementComp->SetDirection(Down);
    }
    else if (dirVector == Point2::Right())
    {
        NextDirection = Right;
        // MovementComp->SetDirection(Right);
    }
    else if (dirVector == Point2::Left())
    {
        NextDirection = Left;
        // MovementComp->SetDirection(Left);
    }
    
}

void IGhost::Scatter(Point2 scatterCoords)
{
    if (MovementComp == nullptr) { return; }
    
    const Directions newDir = Pathfinding::GetDirection(MovementComp->GetCurrentCell(), MovementComp->GetTargetCell() ,scatterCoords);
    // MovementComp->SetDirection(newDir);
    NextDirection = newDir;
}

void IGhost::GetOutOfGhostZone()
{
    if (MovementComp == nullptr) { return; }
    
    std::shared_ptr<GridCell> nextCell = MovementComp->GetTargetCell();

    std::shared_ptr<GridCell> cell = nextCell->Links[0]->Target;
    if (cell->bIsGhostWalkable && cell != MovementComp->GetCurrentCell())
    {
        NextDirection = Up;
        return;
    }

    if (nextCell->Coordinate.GetX() <= 14)
    {
        cell = nextCell->Links[2]->Target;
        
        if (cell->bIsGhostWalkable && cell != MovementComp->GetCurrentCell())
        {
            NextDirection = Right;
        }
    }
    else
    {
        cell = nextCell->Links[3]->Target;
        
        if (cell->bIsGhostWalkable && cell != MovementComp->GetCurrentCell())
        {
            NextDirection = Left;
        }
    }
    

}

void IGhost::SetDirection()
{
    if (MovementComp == nullptr) { return; }
    
   // std::cout << "IGhost::SetDirection: CurrentDirection: " << CurrentDirection << " NextDirection: " << NextDirection << '\n';
    //
    // if(CurrentDirection == None)
    //     CurrentDirection = Right;
    // if(NextDirection == None)
    //     NextDirection = Right;
    if(CurrentDirection == None)
        MovementComp->SetDirection(Left);
    else
        MovementComp->SetDirection(CurrentDirection);
    
    CurrentDirection = NextDirection;
    
}

void IGhost::ChangeCell()
{
    if (GetCell() == nullptr) { return; }
    
    if (PreviousCell != nullptr)
    {
        PreviousCell->OnContentEnters.RemoveListener(CellContentCallback);
    }

    CellContentCallback = GetCell()->OnContentEnters.AddListener([this](std::shared_ptr<GridCellContent>)
    {
        StateMachineComp->CheckForZaku();
    });

    PreviousCell = GetCell();
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

std::shared_ptr<SpriteSwitchComponent> IGhost::GetSpriteComponent()
{
    return SpriteComp;
}

Point2 IGhost::GetTargetCoord()
{
    return Point2{};
}
#pragma endregion 
