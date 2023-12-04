#pragma once

#include "PacmanCore.h"

class GridCell;

class GridMovement
{
    
public:
    void NextCell(std::shared_ptr<GridCell> currentCell, float DeltaTime);
    
    void SetDirection(Directions direction);
    void SetLerpDuration(float duration);

protected:
    Directions currentDirection {};
    Directions newDirection {};


private:
    Point2 LerpPoint2(Point2 p1, Point2 p2, float T);

    Point2 LerpMovement(Point2 start, Point2 target, float DeltaTime);

    float fTimeElapsed = 0;
    float fLerpDuration = 1;
};
