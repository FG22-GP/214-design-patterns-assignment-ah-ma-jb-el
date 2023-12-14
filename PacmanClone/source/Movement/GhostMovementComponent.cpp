#include "PacmanCore.h"
#include "GhostMovementComponent.h"
#include "Grid/GridCell.h"
#include "World/Actors/Actor.hpp"

bool GhostMovementComponent::TrySetNewTargetCell()
{
    if (SteeringDirection == None)
    {
        std::cout << "Stand Still" << std::endl;
        return false;
    }
    std::cout << "TrySetNewTargetCell" << std::endl;

    Directions NewDirection = SteeringDirection;
    std::shared_ptr<GridLink> NewLink = CurrentCell->GetLinkInDirection(NewDirection);
    std::shared_ptr<GridCell> NewTarget = NewLink->Target;

    if(!NewTarget->bIsGhostWalkable)
        return false;
    // for( int i = 0; i < 4; i++)
    // {
    //     NewLink = CurrentCell->GetLinkInDirection(NewDirection);
    //     NewTarget = NewLink->Target;
    //     if(NewTarget->bIsGhostWalkable)
    //     {
    //         break;
    //     }
    //     NewDirection = Point2::Rotate90DegreesClockwise(NewDirection);
    //     
    // }
    TargetCell = NewTarget;
    MoveDirection = NewDirection;
    CurrentLink = NewLink;

    return true;
}

void GhostMovementComponent::OnEnterNewCell(const std::shared_ptr<GridCell>& newCell)
{
    MovementComponent::OnEnterNewCell(newCell);
    ReachedCenterOfCell = false;
    distanceTraveled = 0.f;
}

void GhostMovementComponent::OnReachedCenterOfCell()
{
    ReachedCenterOfCell = true;
    std::cout << "ReachedCenterOfCell" << std::endl;
    OnCenterOfCellEvent.Invoke();
}


void GhostMovementComponent::Move(float DeltaTime)
{
    if(TargetCell == nullptr) { return; }

    const Vector2 CurrentLocation = GetParent()->ActorTransform.GetLocation();
    const Vector2 TargetCellLocation = TargetCell->ActorTransform.GetLocation();
    const Vector2 CurrentCellLocation = CurrentCell->ActorTransform.GetLocation();

    const float DistanceToCurrent = Vector2::Distance(CurrentLocation, CurrentCellLocation);
    const float DistanceToTarget = Vector2::Distance(CurrentLocation, TargetCellLocation);

    if(DistanceToCurrent > DistanceToTarget)
    {
        OnEnterNewCell(TargetCell);
    }
    
    Vector2 MoveVector;

    if(MoveDirection == Up || MoveDirection == Down)
    {
        float MoveValue =  TargetCellLocation.Y - CurrentLocation.Y;
        MoveValue = static_cast<float>((MoveValue > 0) - (MoveValue < 0));
        MoveVector = Vector2(0.0f, MoveValue);
        GetParent()->ActorTransform.SetLocation(Vector2(TargetCellLocation.X, GetParent()->ActorTransform.GetLocation().Y));
    } else
    {
        float MoveValue =  TargetCellLocation.X - CurrentLocation.X;
        MoveValue = static_cast<float>((MoveValue > 0) - (MoveValue < 0));
        MoveVector = Vector2(MoveValue, 0.0f);
        GetParent()->ActorTransform.SetLocation(Vector2(GetParent()->ActorTransform.GetLocation().X, TargetCellLocation.Y));
    }
    
    if (CurrentLink->bIsWrapLink)
        MoveVector.X *= -1;
    
    Vector2 DeltaMovePosition = MoveVector * fMoveSpeed * DeltaTime;

    const float XDistanceToTarget = std::abs(TargetCellLocation.X - CurrentLocation.X);
    const float YDistanceToTarget = std::abs(TargetCellLocation.Y - CurrentLocation.Y);
    
    if(std::abs(DeltaMovePosition.X) > XDistanceToTarget)
    {
        DeltaMovePosition.X = XDistanceToTarget;
    }
    if(std::abs(DeltaMovePosition.Y) > YDistanceToTarget)
    {
        DeltaMovePosition.Y = YDistanceToTarget;
    }

    
    Vector2 NewPosition = CurrentLocation + DeltaMovePosition;

    // Check if center
    // distanceTraveled += Vector2::Magnitude(DeltaMovePosition);
    // std::cout << "distanceTraveled: " << distanceTraveled << std::endl;
    if(Vector2::Distance(NewPosition, TargetCellLocation) < 0.1f)
    {
        OnReachedCenterOfCell();
    }
    
    
    if (NewPosition.X > 28.0f)
        NewPosition.X -= 28.0f;
    if (NewPosition.X < 0.0f)
        NewPosition.X += 28.0f;
    
    GetParent()->ActorTransform.SetLocation(NewPosition);
}
