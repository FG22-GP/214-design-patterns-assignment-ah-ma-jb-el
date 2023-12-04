#include "PacmanCore.h"
#include "GridGenerator.h"
#include "GameGrid.h"
#include "GridCell.h"
#include "GridLink.h"
#include "GridWrapLink.h"
#include "GridCellContent.h"

std::shared_ptr<GameGrid> GridGenerator::GenerateGrid(uint16_t Width, uint16_t Height, std::vector<CellContent> CellContents, std::vector<CellRule> CellRules)
{
	std::shared_ptr<GameGrid> Grid = std::make_shared<GameGrid>(Width, Height);

	// Generate all cells with coordinates, walkable rules and spawn food content.
	for (int i = 0; i < Width * Height; i++)
	{
		std::shared_ptr<GridCell> NewCell = std::make_shared<GridCell>(Grid);
		Point2 Coordinate;
		Coordinate.x = i / Width;
		Coordinate.y = i % Width;
		NewCell->Coordinate = Coordinate;

		switch (CellRules[i])
		{
		case CR_Wall:
			break;
		case CR_Standard:
			NewCell->bIsWalkable = true;
		case CR_Ghost:
			NewCell->bIsGhostWalkable = true;
			break;
		case CR_GhostNoUp:
			NewCell->bIsWalkable = true;
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostCannotWalkUp = true;
			break;
		case CR_GhostSlow:
			NewCell->bIsWalkable = true;
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostIsSlowed = true;
			break;
		}
		
		switch (CellContents[i])
		{
		case CC_Empty:
			break;
		case CC_Dot:
			//TODO: Spawn Dot
			break;
		case CC_Cookie:
			//TODO: Spawn Cookie
			break;
		case CC_Fruit:
			//TODO: Spawn Fruit
			break;
		}

		Grid->Cells[i] = NewCell;

	}

	// Generate Links between cells. 
	// Note that they are ordered according to Point2::AllDirections()'s order of directions.
	for (int i = 0; i < Width * Height; i++)
	{
		Point2 Coord = Grid->Cells[i]->Coordinate;
		for (Point2 Direction : Point2::AllDirections())
		{
			Point2 NeighbourCoord = Coord + Direction;

			// Ugly vector modulo operations for wrapping the board's edges
			bool bIsEdge = true;
			if (NeighbourCoord.x < 0)
				NeighbourCoord.x += Width;
			else if (NeighbourCoord.x >= Width)
				NeighbourCoord.x -= Width;
			else if (NeighbourCoord.y < 0)
				NeighbourCoord.y += Height;
			else if (NeighbourCoord.y >= Height)
				NeighbourCoord.y -= Height;
			else
				bIsEdge = false;

			// If we're wrapping around the edge, we create a GridWrapLink instead of a regular GridLink.
			std::shared_ptr<GridLink> Link = bIsEdge ? std::make_shared<GridWrapLink>() : std::make_shared<GridLink>();

			Link->Source = Grid->Cells[i];
			Link->Target = Grid->GetCellAt(NeighbourCoord);
			Grid->Cells[i]->Links.push_back(Link);
		}
	}

	return Grid;
}