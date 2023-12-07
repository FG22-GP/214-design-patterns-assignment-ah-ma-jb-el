#pragma once

class Actor;

class IGhost
{
public:
    explicit IGhost(const std::shared_ptr<Actor>& pacman);
    virtual ~IGhost() = default;
    virtual void ChasePlayer() = 0;

protected:
    std::shared_ptr<Actor> PacMan;
};
