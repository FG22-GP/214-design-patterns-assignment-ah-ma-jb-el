#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Fruit : public Actor , public IPickUp
{
public:
    void OnPickUp() override;
    int Value() const;

protected:
    int iValue;
};
