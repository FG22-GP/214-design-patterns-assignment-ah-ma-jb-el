#pragma once

#include "PacmanCore.h"
#include "GridLink.h"

class GridCellContent;
class GameGrid;

class GridCell
{

public:
	GridCell(std::shared_ptr<GameGrid> ParentGrid);
	
	bool bIsWalkable;
	bool bIsGhostWalkable;
	bool bGhostCannotWalkUp;
	bool bGhostIsSlowed;

	//Use Directions from Point2.hpp to keep track of indices
	std::vector<std::shared_ptr<GridLink>> Links;

	std::vector<std::shared_ptr<GridCellContent>> Contents;

	std::shared_ptr<GameGrid> Grid;

	Point2 Coordinate;
};

