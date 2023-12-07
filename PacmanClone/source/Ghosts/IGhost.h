#pragma once

class IGhost
{
public:
    virtual ~IGhost() = default;
    virtual void ChasePlayer() = 0;
};
