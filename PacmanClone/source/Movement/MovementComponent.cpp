#include "PacmanCore.h"
#include "MovementComponent.h"
#include "Ghosts/States/StateMachine_Component.h"
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
        std::cout << "No link in direction" << '\n';
        return false;
    }

    Directions NewDirection = SteeringDirection;
    std::shared_ptr<GridLink> NewLink = CurrentCell->GetLinkInDirection(NewDirection);
    std::shared_ptr<GridCell> NewTarget = NewLink->Target;

    if((bIsPlayer && !NewTarget->bIsPlayerWalkable) || (!bIsPlayer && !NewTarget->bIsGhostWalkable)) // Target in steering direction is not walkable
    {
        NewLink = CurrentCell->GetLinkInDirection(MoveDirection);
        NewTarget = NewLink->Target;
        NewDirection = MoveDirection;
        if((bIsPlayer && !NewTarget->bIsPlayerWalkable) || (!bIsPlayer && !NewTarget->bIsGhostWalkable)) // Target in move direction is not walkable
        {
            return false; // Won't update target cell
        }
    }

    TargetCell = NewTarget;
    MoveDirection = NewDirection;
    CurrentCell = NewLink->Target;

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
    OnEnterNewCellEvent.Invoke();
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
    CurrentLink = CurrentCell->GetLinkInDirection(MoveDirection);
    TrySetNewTargetCell();

    bIsPlayer = inIsPlayer;
}
