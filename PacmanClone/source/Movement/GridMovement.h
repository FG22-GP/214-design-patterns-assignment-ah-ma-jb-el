#pragma once

#include "PacmanCore.h"

class GridCell;

class GridMovement
{
    
public:
    //should be tickable
    void NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime);
    
    void SetDirection(Directions direction);

protected:
    Directions currentDirection {};
    Directions newDirection {};
};
