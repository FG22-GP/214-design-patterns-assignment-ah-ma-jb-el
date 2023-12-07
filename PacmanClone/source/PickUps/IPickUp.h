#pragma once

class SpriteComponent;
class GridCellContent;

class IPickUp
{
public:
    virtual ~IPickUp() = default;
    virtual void OnPickUp() = 0;

protected:
    std::shared_ptr<GridCellContent> CellContentComponent;
    std::shared_ptr<SpriteComponent> SpriteComponent;
};
