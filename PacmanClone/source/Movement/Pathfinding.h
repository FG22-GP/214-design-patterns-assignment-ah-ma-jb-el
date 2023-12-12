#pragma once

class GameGrid;
class GridCell;

class Pathfinding
{
public:
    static Directions GetDirection(std::shared_ptr<GridCell> nextCell, std::shared_ptr<GridCell> targetCell); 

private:
    static float Calculate_Distance(std::shared_ptr<GridCell> start, std::shared_ptr<GridCell> goal);
};
