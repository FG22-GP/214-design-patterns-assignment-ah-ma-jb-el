#include "PacmanCore.h"
#include "GridCell.h"

void GridCell::Initialize(std::shared_ptr<GameGrid> ParentGrid)
{
	Grid = ParentGrid;
	bIsPlayerWalkable = false;
	bIsGhostWalkable = false;
	bGhostIsSlowed = false;
	bGhostCannotWalkUp = false;

}

std::shared_ptr<GridLink> GridCell::GetLinkInDirection(GameEngine::Directions Direction)
{
	return Links[(int)(Direction)];
}
