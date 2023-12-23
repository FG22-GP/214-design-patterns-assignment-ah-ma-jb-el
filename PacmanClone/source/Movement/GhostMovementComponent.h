#pragma once

#include "PacmanCore.h"
#include "MovementComponent.h"

class GridLink;
class GridCell;

class GhostMovementComponent : public MovementComponent
{
public:
    GhostMovementComponent(std::shared_ptr<Actor> ParentActor) :
        MovementComponent(ParentActor)
    {
    }

protected:
    void Move(float DeltaTime) override;
    bool TrySetNewTargetCell() override;
    void OnEnterNewCell(const std::shared_ptr<GridCell>& newCell) override;
    

private:
    void OnReachedCenterOfCell();
    
    bool ReachedCenterOfCell = false;
    float distanceTraveled = 0.f;

};
