#pragma once

#include "World\Actors\Actor.hpp"
#include "Grid\GridCellContent.h"
#include "Event\Event.h"

class SpriteComponent;
class GridCellContent;

class IPickUp : public Actor, public GridCellContent
{
public:
    IPickUp(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
        : Actor(ParentWorld, StartTransform) {}
    virtual ~IPickUp() = default;
    virtual void OnPickUp() = 0;

    void BindToCell(std::shared_ptr<GridCell> Cell);
    void UnbindEvent();
    void CheckNewCellContent(std::shared_ptr<GridCellContent> NewContent);

private:
    Event<std::shared_ptr<GridCellContent>>::CallbackPtr EventCallback;
};
