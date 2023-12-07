#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Dot : public Actor , public IPickUp
{
public:
    void OnPickUp() override;
    
};
