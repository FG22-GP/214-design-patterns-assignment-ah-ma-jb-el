#pragma once

#include "PacmanCore.h"

class GridCell;

class GridCellContent
{
public:

	std::shared_ptr<GridCell> GetCell() { return ParentCell; }
	void SetCell(std::shared_ptr<GridCell> NewParent);

private:

	std::shared_ptr<GridCell> ParentCell;

};