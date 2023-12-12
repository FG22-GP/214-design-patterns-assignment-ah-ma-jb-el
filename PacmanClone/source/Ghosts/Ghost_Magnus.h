#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Magnus : public IGhost
{
protected:
    std::shared_ptr<GridCell> GetTargetCell() override;
};
