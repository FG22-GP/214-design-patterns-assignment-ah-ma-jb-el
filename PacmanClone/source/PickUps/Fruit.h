#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Fruit : public IPickUp
{
public:
    void OnPickUp() override;
    int Value() const;

protected:
    int iValue;
};
