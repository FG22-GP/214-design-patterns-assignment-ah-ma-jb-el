#include "PacmanCore.h"
#include "MovementComponent.h"
#include "World\Actors\Actor.hpp"
#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "Grid/GridLink.h"
#include "Grid/GridWrapLink.h"

void MovementComponent::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);
    Move(DeltaTime);
}

bool MovementComponent::TrySetNewTargetCell()
{
    if(!CurrentCell->GetLinkInDirection(SteeringDirection))
    {
        std::cout << "No link in direction" << std::endl;
        return false;
    }

    std::shared_ptr<GridCell> NewTarget = CurrentCell->GetLinkInDirection(SteeringDirection)->Target;
    Directions NewDirection = SteeringDirection;
    
    if(!NewTarget->bIsPlayerWalkable)
    {
        std::cout << "Target cell: " << NewTarget->Coordinate.ToString() << " is not walkable" << std::endl;

        NewTarget = CurrentCell->GetLinkInDirection(MoveDirection)->Target;
        NewDirection = MoveDirection;
        if(!NewTarget->bIsPlayerWalkable)
        {
            std::cout << "Target cell: " << NewTarget->Coordinate.ToString() << " is not walkable" << std::endl;
            return false;
        }
    }
    
    TargetCell = NewTarget;
    MoveDirection = NewDirection;
    std::cout << "New target cell set to: " << TargetCell->Coordinate.ToString() << std::endl;


    
    // targetLink = StartCell->Links[newDirection];
    // targetCell = targetLink->Target;
    // if (targetCell && targetCell->bIsWalkable)
    // {
    //     bWrapLerp = IsWrapLink(targetLink);
    //     TargetCell = targetCell;
    // }

    return true;
}

void MovementComponent::Move(float DeltaTime)
{
    if (!TargetCell) { return; }

    const std::shared_ptr<Actor> Parent = GetParent();
    
    const float DistanceToCurrent = Vector2::Distance(Parent->ActorTransform.GetLocation(), GetCurrentCell()->ActorTransform.GetLocation());
    const float DistanceToTarget = Vector2::Distance(Parent->ActorTransform.GetLocation(), TargetCell->ActorTransform.GetLocation());

    if(DistanceToTarget < DistanceToCurrent)
    {
        OnEnterNewCell(TargetCell);
    }
    
    if (DistanceToTarget < 0.01f)
    {
        return; // We're already there.
    }
    
    float MoveX = TargetCell->ActorTransform.GetLocation().X - Parent->ActorTransform.GetLocation().X;
    float MoveY = TargetCell->ActorTransform.GetLocation().Y - Parent->ActorTransform.GetLocation().Y;
    
    MoveX = static_cast<float>(std::clamp(MoveX, -1.0f, 1.0f));
    MoveY = static_cast<float>(std::clamp(MoveY, -1.0f, 1.0f));

    // Convert to -1, 0, or 1
    MoveX = static_cast<float>((MoveX > 0) - (MoveX < 0));
    MoveY = static_cast<float>((MoveY > 0) - (MoveY < 0));

    const Vector2 MoveVector(MoveX, MoveY);

    
    const float MoveSpeed = 1.0f; // Adjust this speed as needed
    const Vector2 DeltaPosition = MoveVector * MoveSpeed * DeltaTime;
    const Vector2 NewPosition = GetParent()->ActorTransform.GetLocation() + DeltaPosition;
    GetParent()->ActorTransform.SetLocation(NewPosition);

}

Vector2 MovementComponent::WrapLerp(Vector2 start, Vector2 target, float T)
{
    //placeholder
    return CurrentCell->Coordinate;
}

bool MovementComponent::IsWrapLink(std::shared_ptr<GridLink>& link)
{
    std::shared_ptr<GridWrapLink> wraplink = std::static_pointer_cast<GridWrapLink>(link);

    return wraplink != nullptr;
}

void MovementComponent::OnEnterNewCell(const std::shared_ptr<GridCell>& newCell)
{
    if (const std::shared_ptr<GridCellContent> ParentAsGridCellContent = std::dynamic_pointer_cast<GridCellContent>(Parent))
    {
        ParentAsGridCellContent->SetCell(newCell);
    }
    CurrentCell = newCell;
    TrySetNewTargetCell();

}

void MovementComponent::SetDirection(Directions newDirection)
{
    SteeringDirection = newDirection;
    TrySetNewTargetCell();
}

void MovementComponent::Init(std::shared_ptr<GridCell> startCell)
{
    CurrentCell = std::move(startCell);
    SetDirection(Right);

    TargetCell = CurrentCell->Links[SteeringDirection]->Target;
    TrySetNewTargetCell();
}

