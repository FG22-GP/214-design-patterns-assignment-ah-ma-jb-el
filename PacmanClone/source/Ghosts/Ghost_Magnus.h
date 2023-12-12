#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Magnus : public IGhost
{
public:
    void ChasePlayer() override;
    
};
