#pragma once
#include "PacmanCore.h"

class GameGrid;

enum CellContent
{
	CC_Empty = 0,
	CC_Dot = 1,
	CC_Cookie = 2,
	CC_Fruit = 3,
};

enum CellRule
{
	CR_Wall = 0,
	CR_Standard = 1,
	CR_Ghost = 2,
	CR_GhostNoUp = 3,
	CR_GhostSlow = 4
};


class GridGenerator
{

public:
	std::shared_ptr<GameGrid> GenerateGrid(uint16_t Width, uint16_t Height, std::vector<CellContent> CellContents, std::vector<CellRule> CellRules);
};
