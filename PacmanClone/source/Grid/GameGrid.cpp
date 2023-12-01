#include "PacmanCore.h"
#include "GameGrid.h"

GameGrid::GameGrid(uint16_t Width, uint16_t Height)
{
	this->Width = Width;
	this->Height = Height;

	Cells.resize(Width * Height);

	/*
	for (int i = 0; i < Width * Height; i++)
	{
		Cells[i] = std::make_shared<GridCell>(shared_from_this());
	}
	*/
}

std::shared_ptr<GridCell> GameGrid::GetCellAt(const Point2& Coordinate) const
{
	if (Coordinate.x < 0 || Coordinate.y < 0 || Coordinate.x >= Width || Coordinate.y >= Height)
		return nullptr;
	uint16_t Index = Coordinate.x * Width + Coordinate.y;
	return Cells[Index];
}

Point2 GameGrid::GetCoordinateOf(const std::shared_ptr<GridCell> Cell) const
{
	for (int i = 0; i < Width * Height; i++)
	{
		if (Cell == Cells[i])
		{
			Point2 P;
			P.x = i / Width;
			P.y = i % Height;
			return P;
		}
	}
	return Point2();
}
