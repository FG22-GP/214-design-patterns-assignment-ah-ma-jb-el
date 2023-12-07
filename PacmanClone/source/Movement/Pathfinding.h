#pragma once

class GameGrid;
class GridCell;

class Pathfinding
{
public:
    std::vector<std::shared_ptr<GridCell>> Dijkstra(std::shared_ptr<GridCell> start, std::shared_ptr<GridCell> goal, std::shared_ptr<GameGrid> grid);

private:
    struct Node
    {
        std::shared_ptr<GridCell> cell;
        int totalCost;
        std::shared_ptr<Node> parent;

        bool operator>(const Node& other) const
        {
            return totalCost > other.totalCost;
        }
    };
};
