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
    if(SteeringDirection == Directions::None)
    {
        return false; // Stand Still
    }
    
    if(!CurrentCell->GetLinkInDirection(SteeringDirection))
    {
        std::cout << "No link in direction" << '\n';
        return false;
    }

    Directions NewDirection = SteeringDirection;
    //std::shared_ptr<GridLink> NewLink = CurrentCell->GetLinkInDirection(SteeringDirection);
    std::shared_ptr<GridCell> NewTarget = CurrentCell->GetLinkInDirection(SteeringDirection)->Target;

    if((bIsPlayer && !NewTarget->bIsPlayerWalkable) || (!bIsPlayer && !NewTarget->bIsGhostWalkable)) // Target in steering direction is not walkable
    {
        //CurrentCell->GetLinkInDirection(SteeringDirection) = CurrentCell->GetLinkInDirection(MoveDirection);
        NewTarget = CurrentCell->GetLinkInDirection(MoveDirection)->Target;
        NewDirection = MoveDirection;
        if((bIsPlayer && !NewTarget->bIsPlayerWalkable) || (!bIsPlayer && !NewTarget->bIsGhostWalkable)) // Target in move direction is not walkable
        {
            return false; // Won't update target cell
        }
    }

    CurrentLink = CurrentCell->GetLinkInDirection(MoveDirection);
    TargetCell = NewTarget;
    MoveDirection = NewDirection;
    //CurrentCell = NewLink->Target;

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
        OnCenterOfCellEvent.Invoke();
        return; // We're already there. 
    }
    
    float MoveX = TargetCellLocation.X - CurrentLocation.X;
    float MoveY = TargetCellLocation.Y - CurrentLocation.Y;

    // Convert to -1, 0, or 1
    MoveX = static_cast<float>((MoveX > 0) - (MoveX < 0));
    MoveY = static_cast<float>((MoveY > 0) - (MoveY < 0));
    if (CurrentLink->bIsWrapLink)
        MoveX *= -1;

    const float XDistanceToTarget = TargetCellLocation.X - CurrentLocation.X;
    const float YDistanceToTarget = TargetCellLocation.Y - CurrentLocation.Y;
    
    const Vector2 MoveVector(MoveX, MoveY);
    
    Vector2 DeltaPosition = MoveVector * fMoveSpeed * DeltaTime;
    
    if(std::abs(DeltaPosition.X) > std::abs(XDistanceToTarget))
    {
        DeltaPosition.X = XDistanceToTarget;
    }
    if(std::abs(DeltaPosition.Y) > std::abs(YDistanceToTarget))
    {
        DeltaPosition.Y = YDistanceToTarget;
    }
    
    Vector2 NewPosition = CurrentLocation + DeltaPosition;
    if (NewPosition.X > 28.0f)
        NewPosition.X -= 28.0f;
    if (NewPosition.X < 0.0f)
        NewPosition.X += 28.0f;
    GetParent()->ActorTransform.SetLocation(NewPosition);

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
    TrySetNewTargetCell();
    OnEnterNewCellEvent.Invoke();
}

void MovementComponent::SetDirection(Directions newDirection)
{
    if (CurrentLink->bIsWrapLink)
        return;
    SteeringDirection = newDirection;
    TrySetNewTargetCell();
}

void MovementComponent::Init(std::shared_ptr<GridCell> startCell, bool inIsPlayer)
{
    CurrentCell = std::move(startCell);
    MoveDirection = Directions::Right;
    TargetCell = CurrentCell;
    CurrentLink = CurrentCell->GetLinkInDirection(MoveDirection);
    TrySetNewTargetCell();

    bIsPlayer = inIsPlayer;
}
