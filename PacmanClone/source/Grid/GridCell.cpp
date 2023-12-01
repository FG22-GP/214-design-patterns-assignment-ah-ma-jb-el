#include "PacmanCore.h"
#include "GridCell.h"

GridCell::GridCell(std::shared_ptr<GameGrid> ParentGrid)
{
	Links.resize(4);
	Grid = ParentGrid;
}