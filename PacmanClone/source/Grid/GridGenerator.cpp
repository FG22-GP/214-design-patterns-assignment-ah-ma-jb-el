#include "PacmanCore.h"
#include "GridGenerator.h"
#include "GameGrid.h"
#include "GridCell.h"
#include "GridLink.h"
#include "GridCellContent.h"

std::shared_ptr<GameGrid> GridGenerator::GenerateGrid(uint16_t Width, uint16_t Height, std::vector<CellContent> CellContents, std::vector<CellRule> CellRules)
{
	std::shared_ptr<GameGrid> Grid = std::make_shared<GameGrid>(Width, Height);

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
			//Spawn Dot
			break;
		case CC_Cookie:
			//Spawn Cookie
			break;
		case CC_Fruit:
			//Spawn Fruit
			break;
		}

		Grid->Cells[i] = NewCell;

	}

	//Generate Links between cells


	return Grid;
}
