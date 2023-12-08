#include "PacmanCore.h"
#include "GridGenerator.h"
#include "GameGrid.h"
#include "GridCell.h"
#include "GridLink.h"
#include "GridWrapLink.h"
#include "GridCellContent.h"
#include "World\World.hpp"

std::shared_ptr<GameGrid> GridGenerator::GenerateGrid(std::shared_ptr<World> ParentWorld, uint16_t Width, uint16_t Height, std::vector<CellContent> CellContents, std::vector<CellRule> CellRules)
{
	std::shared_ptr<GameGrid> Grid = std::make_shared<GameGrid>(Width, Height);

	// Generate all cells with coordinates, walkable rules and spawn food content.
	for (int i = 0; i < Width * Height; i++)
	{
		std::shared_ptr<GridCell> NewCell = ParentWorld->CreateActor<GridCell>();
		Point2 Coordinate(i % Width, i / Width);
		NewCell->Coordinate = Coordinate;
		NewCell->ActorTransform.SetLocation(Coordinate);

		switch (CellRules[i])
		{
		case CR_Wall:
			NewCell->bIsPlayerWalkable = false;
			NewCell->bIsGhostWalkable = false;
			NewCell->bGhostCannotWalkUp = false;
			NewCell->bGhostIsSlowed = false;
			break;
		case CR_Standard:
			NewCell->bIsPlayerWalkable = true; 
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostCannotWalkUp = false;
			NewCell->bGhostIsSlowed = false;
		case CR_Ghost:
			NewCell->bIsPlayerWalkable = false; 
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostCannotWalkUp = false;
			NewCell->bGhostIsSlowed = false;
			break;
		case CR_GhostNoUp:
			NewCell->bIsPlayerWalkable = true;
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostCannotWalkUp = true;
			NewCell->bGhostIsSlowed = false;
			break;
		case CR_GhostSlow:
			NewCell->bIsPlayerWalkable = true;
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostCannotWalkUp = false;
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
			if (NeighbourCoord.GetX() < 0)
				NeighbourCoord.SetX(NeighbourCoord.GetX() + Width);
			else if (NeighbourCoord.GetX() >= Width)
				NeighbourCoord.SetX(NeighbourCoord.GetX() - Width);
			else if (NeighbourCoord.GetY() < 0)
				NeighbourCoord.SetY(NeighbourCoord.GetY() + Height);
			else if (NeighbourCoord.GetY() >= Height)
				NeighbourCoord.SetY(NeighbourCoord.GetY() - Height);
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
