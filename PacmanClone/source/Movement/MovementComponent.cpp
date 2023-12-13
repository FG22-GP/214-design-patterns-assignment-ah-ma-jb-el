﻿#include "PacmanCore.h"
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
    if(SteeringDirection == Directions::None)
    {
        return false; // Stand Still
    }
    
    if(!CurrentCell->GetLinkInDirection(SteeringDirection))
    {
        std::cout << "No link in direction" << std::endl;
        return false;
    }
    
    std::shared_ptr<GridCell> NewTarget = CurrentCell->GetLinkInDirection(SteeringDirection)->Target;
    Directions NewDirection = SteeringDirection;


    if((bIsPlayer && !NewTarget->bIsPlayerWalkable) || (!bIsPlayer && !NewTarget->bIsGhostWalkable))
    {
        //std::cout << "Target cell: " << NewTarget->Coordinate.ToString() << " is not walkable" << std::endl;
    
        NewTarget = CurrentCell->GetLinkInDirection(MoveDirection)->Target;
        NewDirection = MoveDirection;
        if((bIsPlayer && !NewTarget->bIsPlayerWalkable) || (!bIsPlayer && !NewTarget->bIsGhostWalkable))
        {
            // std::cout << "Target cell: " << NewTarget->Coordinate.ToString() << " is not walkable" << std::endl;
            return false;
        }
    }
    
    TargetCell = NewTarget;
    MoveDirection = NewDirection;

    // TODO: Implement wrap links

    return true;
}

void MovementComponent::Move(float DeltaTime)
{
    if (!TargetCell) { return; }

    const Vector2 CurrentLocation = GetParent()->ActorTransform.GetLocation();
    const Vector2 TargetCellLocation = TargetCell->ActorTransform.GetLocation();
    const Vector2 CurrentCellLocation = CurrentCell->ActorTransform.GetLocation();

    const float DistanceToCurrent = Vector2::Distance(CurrentLocation, CurrentCellLocation);
    const float DistanceToTarget = Vector2::Distance(CurrentLocation, TargetCellLocation);

    if(DistanceToTarget < DistanceToCurrent)
    {
        OnEnterNewCell(TargetCell);
    }
    
    if (DistanceToTarget < 0.01f)
    {
        return; // We're already there. // TODO: Fire event here?
    }
    
    float MoveX = TargetCellLocation.X - CurrentLocation.X;
    float MoveY = TargetCellLocation.Y - CurrentLocation.Y;

    // Convert to -1, 0, or 1
    MoveX = static_cast<float>((MoveX > 0) - (MoveX < 0));
    MoveY = static_cast<float>((MoveY > 0) - (MoveY < 0));

    // Removes shaking but causes slower movement on tile switch TODO: Fix this
    const float XDistanceToTarget = TargetCellLocation.X - CurrentLocation.X;
    const float YDistanceToTarget = TargetCellLocation.Y - CurrentLocation.Y;
    
    if(std::abs(MoveX) > std::abs(XDistanceToTarget) )
    {
        MoveX = XDistanceToTarget;
    }
    if(std::abs(MoveY) > std::abs(YDistanceToTarget) )
    {
        MoveY = YDistanceToTarget;
    }

    const Vector2 MoveVector(MoveX, MoveY);
    
    const Vector2 DeltaPosition = MoveVector * fMoveSpeed * DeltaTime;
    const Vector2 NewPosition = CurrentLocation + DeltaPosition;
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

void MovementComponent::Init(std::shared_ptr<GridCell> startCell, bool inIsPlayer)
{
    CurrentCell = std::move(startCell);
    MoveDirection = Directions::Right;
    TargetCell = CurrentCell;
    TrySetNewTargetCell();

    bIsPlayer = inIsPlayer;
}

