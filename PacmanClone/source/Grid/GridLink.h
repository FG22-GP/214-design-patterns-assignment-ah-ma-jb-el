#pragma once

#include "PacmanCore.h"

class GridCell;

class GridLink
{

public:

	std::shared_ptr<GridCell> Source, Target;

};

