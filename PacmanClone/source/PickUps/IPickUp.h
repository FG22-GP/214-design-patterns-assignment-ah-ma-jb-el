#pragma once

#include "World\Actors\Actor.hpp"
#include "Grid\GridCellContent.h"
#include "Event\Event.h"

class SpriteComponent;
class GridCellContent;

class IPickUp : public Actor, public GridCellContent
{
public:
    IPickUp(std::shared_ptr<GridCell> NewParent);
    virtual ~IPickUp() = default;
    virtual void OnPickUp() = 0;

    void CheckNewCellContent(std::shared_ptr<GridCellContent> NewContent);

private:
    Event<std::shared_ptr<GridCellContent>>::CallbackPtr EventCallback;
    void UnbindEvent();
};
