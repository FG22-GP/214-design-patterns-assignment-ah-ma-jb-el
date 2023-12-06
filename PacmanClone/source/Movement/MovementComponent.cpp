#include "PacmanCore.h"
#include "MovementComponent.h"

#include "Engine/World/Actors/Actor.hpp"
#include "Grid/GridCell.h"
#include "Grid/GridLink.h"
#include "Grid/GridWrapLink.h"

void MovementComponent::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    NextCell();
    LerpMovement(DeltaTime);
}

void MovementComponent::NextCell()
{
    if (StartCell != nullptr && TargetCell != nullptr) { return; }

    /*
    Should be something like
    StartCell = actor->GetComponent->GetCurrentCell
    */
    
    std::shared_ptr<GridLink> targetLink = StartCell->Links[newDirection];
    std::shared_ptr<GridCell> targetCell = targetLink->Target;
    if (targetLink->Target != nullptr && targetLink->Target->bIsWalkable)
    {
        bWrapLerp = IsWrapLink(targetLink);
        TargetCell = targetCell;
        currentDirection = newDirection;
        return;
    }
    
    targetLink = StartCell->Links[newDirection];
    targetCell = targetLink->Target;
    if (targetCell != nullptr && targetCell->bIsWalkable)
    {
        bWrapLerp = IsWrapLink(targetLink);
        TargetCell = targetCell;
    }
}

void MovementComponent::LerpMovement(float DeltaTime)
{
    if (StartCell == nullptr || TargetCell == nullptr) { return; }
    
    if (fTimeElapsed < fLerpDuration)
    {
        fTimeElapsed += DeltaTime;

        if (fTimeElapsed > fLerpDuration / 2 - DeltaTime / 2 &&
            fTimeElapsed < fLerpDuration / 2 + DeltaTime / 2)
        {
            //event here: half way through lerp !!
        }

        Vector2 newPosition = bWrapLerp?
            WrapLerp(StartCell->Coordinate, TargetCell->Coordinate, fTimeElapsed/fLerpDuration) :
            Vector2::Lerp(StartCell->Coordinate, TargetCell->Coordinate, fTimeElapsed/fLerpDuration);
        
        Parent->ActorTransform.SetLocation(newPosition);
    }
    else
    {
        Parent->ActorTransform.SetLocation(TargetCell->Coordinate);
        StartCell = nullptr;
        TargetCell = nullptr;
        fTimeElapsed = 0;
    }

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

void MovementComponent::SetDirection(Directions direction)
{
    newDirection = direction;
}

void MovementComponent::SetLerpDuration(float duration)
{
    fLerpDuration = duration;
}

