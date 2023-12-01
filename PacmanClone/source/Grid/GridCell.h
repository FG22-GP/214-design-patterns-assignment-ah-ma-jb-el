#pragma once

#include "PacmanCore.h"
#include "GridLink.h"

class GridCell
{

public:
	GridCell();
	
	bool bIsWalkable;

	//Use Directions from Point2.hpp to keep track of indices
	std::vector<std::shared_ptr<GridLink>> Links;

	
};

