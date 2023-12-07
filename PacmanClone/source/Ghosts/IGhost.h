#pragma once

class SpriteComponent;
class GridCellContent;
class MovementComponent;
class StateMachine_Component;
class GridCell;
class Actor;

class IGhost
{
public:
    virtual ~IGhost() = default;
    virtual void ChasePlayer() = 0;
    virtual void Flee() = 0;
    virtual void Scatter(std::shared_ptr<GridCell> scatterCell) = 0;

protected:
    std::shared_ptr<Actor> PacMan;
    std::shared_ptr<StateMachine_Component> StateMachineComponent;
    std::shared_ptr<MovementComponent> MovementComponent;
    std::shared_ptr<GridCellContent> CellContentComponent;
    std::shared_ptr<SpriteComponent> SpriteComponent;
};
