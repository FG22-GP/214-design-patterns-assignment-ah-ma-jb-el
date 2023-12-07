#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Cookie : public Actor , public IPickUp
{
public:
    void OnPickUp() override;
    
};
