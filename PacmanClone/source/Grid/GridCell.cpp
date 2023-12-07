#include "PacmanCore.h"
#include "GridCell.h"

GridCell::GridCell(std::shared_ptr<GameGrid> ParentGrid)
{
	Grid = ParentGrid;
	bIsWalkable = false;
	bIsGhostWalkable = false;
	bGhostIsSlowed = false;
	bGhostCannotWalkUp = false;

}

std::shared_ptr<GridLink> GridCell::GetLinkInDirection(GameEngine::Directions Direction)
{
	return Links[(int)(Direction)];
}
