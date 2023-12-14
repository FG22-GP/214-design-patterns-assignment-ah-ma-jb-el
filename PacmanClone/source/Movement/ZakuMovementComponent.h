#pragma once

#include "PacmanCore.h"
#include "MovementComponent.h"

class GridLink;
class GridCell;

class ZakuMovementComponent : public MovementComponent
{
public:
    ZakuMovementComponent(std::shared_ptr<Actor> ParentActor) :
        MovementComponent(ParentActor)
    {
    }

protected:
    virtual void Move(float DeltaTime) override;
    virtual bool TrySetNewTargetCell() override;
};
