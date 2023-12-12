#pragma once

class GameGrid;
class GridCell;

class Pathfinding
{
public:
    static Directions GetDirection(std::shared_ptr<GridCell> currentCell, std::shared_ptr<GridCell> nextCell, Point2 targetCoord); 

    static float Calculate_Distance(std::shared_ptr<GridCell> start, Point2 goal);

};
