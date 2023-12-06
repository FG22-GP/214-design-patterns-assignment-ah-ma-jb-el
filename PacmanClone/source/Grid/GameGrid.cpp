#include "PacmanCore.h"
#include "GameGrid.h"

GameGrid::GameGrid(uint16_t Width, uint16_t Height)
{
	this->Width = Width;
	this->Height = Height;

	Cells.resize(Width * Height);
}

std::shared_ptr<GridCell> GameGrid::GetCellAt(const Point2& Coordinate) const
{
	if (Coordinate.GetX() < 0 || Coordinate.GetY() < 0 || 
		Coordinate.GetX() >= Width || Coordinate.GetY() >= Height)
		return nullptr;

	uint16_t Index = Coordinate.GetX() * Width + Coordinate.GetY();
	return Cells[Index];
}

Point2 GameGrid::GetCoordinateOf(const std::shared_ptr<GridCell> Cell) const
{
	for (int i = 0; i < Width * Height; i++)
	{
		if (Cell == Cells[i])
		{
			return Point2(
				i / Width,
				i % Height
			);
		}
	}
	return Point2();
}
