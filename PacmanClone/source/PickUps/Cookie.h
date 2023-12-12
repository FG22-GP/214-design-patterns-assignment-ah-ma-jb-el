#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Cookie : public IPickUp
{
public:
    Cookie(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) : IPickUp(ParentWorld, StartTransform)
    {

    }

    void OnPickUp() override;
    
};
