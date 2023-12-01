#pragma once

#include "PacmanCore.h"

class GridCell;

class GridMovement
{
    
public:
    std::shared_ptr<GridCell> NextCell(std::shared_ptr<GridCell> currentCell);
    void SetDirection(Directions direction);

protected:
    Directions currentDirection {};
    Directions newDirection {};
};
