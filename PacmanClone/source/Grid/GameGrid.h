#pragma once

#include "PacmanCore.h"
#include "GridCell.h"

class GameGrid : public std::enable_shared_from_this<GameGrid>
{
public:
	GameGrid(uint16_t Width, uint16_t Height);
	std::vector<std::shared_ptr<GridCell>> Cells;

	uint16_t GetWidth() const { return Width; }
	uint16_t GetHeight() const { return Height; }

	std::shared_ptr<GridCell> GetCellAt(const Point2& Coordinate) const;
	Point2 GetCoordinateOf(const std::shared_ptr<GridCell> Cell) const;

private:
	uint16_t Width, Height;
};

