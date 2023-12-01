#include "PacmanCore.h"
#include "GridCell.h"

GridCell::GridCell(std::shared_ptr<GameGrid> ParentGrid)
{
	Links.resize(4);
	Grid = ParentGrid;
}

std::shared_ptr<GridLink> GridCell::GetLinkInDirection(GameEngine::Directions Direction)
{
	return Links[(int)(Direction)];
}
