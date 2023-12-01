#pragma once

#include "PacmanCore.h"
#include "GridCell.h"

class GameGrid
{
public:

	uint16_t Width, Height;
	std::vector<std::shared_ptr<GridCell>> Cells;

	GameGrid(uint16_t Width, uint16_t Height);

	std::shared_ptr<GridCell> GetCellAt(const Point2& Coordinate) const;
	Point2 GetCoordinateOf(const std::shared_ptr<GridCell> Cell) const;
};

