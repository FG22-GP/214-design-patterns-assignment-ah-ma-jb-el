#include "PacmanCore.h"
#include "MovementComponent.h"
#include "Ghosts/States/StateMachine_Component.h"
#include "World\Actors\Actor.hpp"
#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "Grid/GridLink.h"

void MovementComponent::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);
    Move(DeltaTime);
}

bool MovementComponent::TrySetNewTargetCell()
{
    return false;
}

void MovementComponent::Move(float DeltaTime)
{
}

Vector2 MovementComponent::WrapLerp(Vector2 start, Vector2 target, float T)
{
    //placeholder
    return CurrentCell->Coordinate;
}

bool MovementComponent::IsWrapLink(std::shared_ptr<GridLink>& link)
{
    return link->bIsWrapLink;
}

void MovementComponent::OnEnterNewCell(const std::shared_ptr<GridCell>& newCell)
{
    if (const std::shared_ptr<GridCellContent> ParentAsGridCellContent = std::dynamic_pointer_cast<GridCellContent>(Parent))
    {
        ParentAsGridCellContent->SetCell(newCell);
    }
    CurrentCell = newCell;
    std::cout << "OnEnterNewCell" << std::endl;
    TrySetNewTargetCell();
    OnEnterNewCellEvent.Invoke();
}

void MovementComponent::SetDirection(Directions newDirection)
{
    SteeringDirection = newDirection;
    if (CurrentLink->bIsWrapLink)
    {
        std::cout << "WrapLink" << std::endl;
        return;
    }
    TrySetNewTargetCell();

    std::cout << "SetDirection" << std::endl;
}

void MovementComponent::Init(std::shared_ptr<GridCell> startCell, Directions startDirection)
{
    CurrentCell = std::move(startCell);
    MoveDirection = startDirection;
    TargetCell = CurrentCell;
    CurrentLink = CurrentCell->GetLinkInDirection(MoveDirection);
    std::cout << "Init" << std::endl;
    TrySetNewTargetCell();
}
