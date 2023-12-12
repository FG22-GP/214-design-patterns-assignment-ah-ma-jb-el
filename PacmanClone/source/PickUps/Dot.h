#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Dot : public IPickUp
{
public:
    void OnPickUp() override;
    
};
