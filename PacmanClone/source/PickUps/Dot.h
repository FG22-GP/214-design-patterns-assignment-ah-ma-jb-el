#pragma once
#include "IPickUp.h"
#include "World/Actors/Actor.hpp"

class Dot : public IPickUp
{
public:
    Dot(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) : IPickUp(ParentWorld, StartTransform)
    {
        
    }

    void OnPickUp() override;
    
};
