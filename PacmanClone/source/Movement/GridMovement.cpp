#include "PacmanCore.h"
#include "GridMovement.h"

#include "Engine/World/Actors/Actor.hpp"
#include "Grid/GridCell.h"
#include "Grid/GridLink.h"
#include "Grid/GridWrapLink.h"

void GridMovement::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    NextCell(nullptr, DeltaTime);
    LerpMovement(DeltaTime);
}

void GridMovement::NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime)
{
    if (StartCell != nullptr && TargetCell != nullptr) { return; }

    //should be something like StartCell = actor->GetComponent->GetCurrentCell in future !
    StartCell = currentCell;
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

void GridMovement::LerpMovement(float DeltaTime)
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

Vector2 GridMovement::WrapLerp(Vector2 start, Vector2 target, float T)
{
    return Vector2(0,0);
}

bool GridMovement::IsWrapLink(std::shared_ptr<GridLink>& link)
{
    std::shared_ptr<GridWrapLink> wraplink = std::static_pointer_cast<GridWrapLink>(link);

    return wraplink != nullptr;
}

void GridMovement::SetDirection(Directions direction)
{
    newDirection = direction;
}

void GridMovement::SetLerpDuration(float duration)
{
    fLerpDuration = duration;
}

