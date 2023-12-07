#include "PacmanCore.h"
#include "Pathfinding.h"

#include <queue>

#include "Grid/GridCell.h"
#include "Grid/GridLink.h"

std::vector<std::shared_ptr<GridCell>> Pathfinding::Dijkstra(
    std::shared_ptr<GridCell> start,
    std::shared_ptr<GridCell> goal,
    std::shared_ptr<GameGrid> grid)
{
    std::list<Node> open;
    std::unordered_set<std::shared_ptr<GridCell>> closed;

    std::vector<std::shared_ptr<GridCell>> path;

    /*
    open.push_back({start, 0, nullptr});
    
    while (!open.empty())
    {
        Node current {};
        for (Node node : open)
        {
            int currentLowest = 999;
            if (node.totalCost < currentLowest)
            {
                currentLowest = node.totalCost;
                current = node;
            }
        }
    
        if (current.cell == goal)
        {
            while (current.cell != start)
            {
                path.push_back(current.cell);
                current.cell = current.parent->cell;
            }
            std::ranges::reverse(path);
            return path;
        }
    
        
        closed.insert(current.cell);
    
        for (std::shared_ptr<GridLink> link : current.cell->Links)
        {
            Node neighbour = {link->Target, 0, nullptr};
            if (!neighbour.cell->bIsWalkable || closed.contains(neighbour.cell)) { continue; }
    
            int currentTotal = current.totalCost + 1;
    
            bool isNew = false;
    
            auto iterator = std::find(open.begin(), open.end(), neighbour);
            
            if (iterator != open.end()) { isNew = true; }
    
            if (isNew || currentTotal < current.totalCost)
            {
                std::shared_ptr<Node> neighbourPtr(&current, [](Node*){});
                neighbour.parent = neighbourPtr;
                neighbour.totalCost = currentTotal;
    
                if (isNew)
                {
                    open.push_back(neighbour);
                }
            }
        }
    }

    */
    return path;
}