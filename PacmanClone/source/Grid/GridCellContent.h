#pragma once

#include "PacmanCore.h"

class GridCell;

class GridCellContent
{
public:
	virtual ~GridCellContent() = default;

	std::shared_ptr<GridCell> GetCell() { return ParentCell; }
	void SetCell(std::shared_ptr<GridCell> NewParent);

private:

	std::shared_ptr<GridCell> ParentCell;

};