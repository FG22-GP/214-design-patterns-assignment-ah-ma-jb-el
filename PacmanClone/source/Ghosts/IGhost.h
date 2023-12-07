#pragma once

class GridCell;
class Actor;

class IGhost
{
public:
    explicit IGhost(const std::shared_ptr<Actor>& pacman);
    virtual ~IGhost() = default;
    virtual void ChasePlayer() = 0;
    virtual void Flee() = 0;
    virtual void Scatter(std::shared_ptr<GridCell> scatterCell) = 0;

protected:
    std::shared_ptr<Actor> PacMan;
};
