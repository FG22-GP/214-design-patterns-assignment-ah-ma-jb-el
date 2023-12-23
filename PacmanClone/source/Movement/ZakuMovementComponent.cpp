#include "PacmanCore.h"
#include "ZakuMovementComponent.h"

#include "World\Actors\Actor.hpp"
#include "Grid/GridCell.h"

bool ZakuMovementComponent::TrySetNewTargetCell()
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

    if(!NewTarget->bIsPlayerWalkable) // Target in steering direction is not walkable
    {
        //CurrentCell->GetLinkInDirection(SteeringDirection) = CurrentCell->GetLinkInDirection(MoveDirection);
        NewTarget = CurrentCell->GetLinkInDirection(MoveDirection)->Target;
        NewDirection = MoveDirection;
        if(!NewTarget->bIsPlayerWalkable)  // Target in move direction is not walkable
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

void ZakuMovementComponent::Move(float DeltaTime)
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
    
    float MoveX = TargetCellLocation.X - CurrentLocation.X;
    float MoveY = TargetCellLocation.Y - CurrentLocation.Y;

    // Convert to -1, 0, or 1
    MoveX = static_cast<float>((MoveX > 0) - (MoveX < 0));
    MoveY = static_cast<float>((MoveY > 0) - (MoveY < 0));
    
    if (CurrentLink->bIsWrapLink)
        MoveX *= -1;

    const Vector2 MoveVector(MoveX, MoveY);
    
    Vector2 DeltaPosition = MoveVector * fMoveSpeed * DeltaTime;

    const float XDistanceToTarget = std::abs(TargetCellLocation.X - CurrentLocation.X);
    const float YDistanceToTarget = std::abs(TargetCellLocation.Y - CurrentLocation.Y);
    
    if(std::abs(DeltaPosition.X) > XDistanceToTarget)
    {
        DeltaPosition.X = XDistanceToTarget;
    }
    if(std::abs(DeltaPosition.Y) > YDistanceToTarget)
    {
        DeltaPosition.Y = YDistanceToTarget;
    }
    
    Vector2 NewPosition = CurrentLocation + DeltaPosition;
    
    if (NewPosition.X > 28.0f)
        NewPosition.X -= 28.0f;
    if (NewPosition.X < 0.0f)
        NewPosition.X += 28.0f;
    
    GetParent()->ActorTransform.SetLocation(NewPosition);


#pragma region Rotate
    float Rotation = 0.0f;
    switch (MoveDirection)
    {
    case 0:
        Rotation = 270.0f;
        break;
    case 1:
        Rotation = 90.0f;
        break;
    case 2:
        Rotation = 0.0f;
        break;
    case 3:
        Rotation = 180.0f;
        break;
    }
    GetParent()->ActorTransform.SetRotation(Rotation);
#pragma endregion DetermineRotation
}
