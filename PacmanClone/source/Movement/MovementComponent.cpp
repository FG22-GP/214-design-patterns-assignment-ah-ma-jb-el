#include "PacmanCore.h"
#include "MovementComponent.h"
#include "World\Actors\Actor.hpp"
#include "Grid/GridCell.h"
#include "Grid/GridLink.h"
#include "Grid/GridWrapLink.h"

void MovementComponent::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);
    if(currentDirection != cachedDirection)
        TrySetNewTargetCell();
    Move(DeltaTime);
}

void MovementComponent::TrySetNewTargetCell()
{
    const auto NewTarget = GetCurrentCell()->GetLinkInDirection(cachedDirection)->Target;
    if(NewTarget->bIsPlayerWalkable)
    {
        TargetCell = NewTarget;
        currentDirection = cachedDirection;
    }
}

void MovementComponent::Move(float DeltaTime)
{
    if (!TargetCell) { return; }
    //
    // const float DistanceToTarget = Vector2::Distance(GetCurrentCell()->Coordinate, TargetCell->Coordinate);
    // if (DistanceToTarget < 0.01f)
    // {
    //     return; // We're already there.
    // }
    //
    // Vector2 MoveVector = GetCurrentCell()->Coordinate - TargetCell->Coordinate;
    // Vector2::Normalize(MoveVector);
    //
    // const float MoveSpeed = 1.0f; // Adjust this speed as needed
    // const Vector2 DeltaPosition = MoveVector * MoveSpeed * DeltaTime;
    // const Vector2 NewPosition = GetParent()->ActorTransform.GetLocation() + DeltaPosition;
    // GetParent()->ActorTransform.SetLocation(NewPosition);
}

Vector2 MovementComponent::WrapLerp(Vector2 start, Vector2 target, float T)
{
    //placeholder
    return StartCell->Coordinate;
}

bool MovementComponent::IsWrapLink(std::shared_ptr<GridLink>& link)
{
    std::shared_ptr<GridWrapLink> wraplink = std::static_pointer_cast<GridWrapLink>(link);

    return wraplink != nullptr;
}

void MovementComponent::SetDirection(Directions newDirection)
{
    cachedDirection = newDirection;
    if(DirectionHelpers::IsOpposingDirection(currentDirection, newDirection)) 
    {
        TrySetNewTargetCell();
    }
}

void MovementComponent::Init(std::shared_ptr<GridCell> startCell)
{
    StartCell = std::move(startCell);
    SetDirection(Directions::Right);
    TargetCell = StartCell->Links[Directions::Right]->Target;
}
