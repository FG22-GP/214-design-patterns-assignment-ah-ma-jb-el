#pragma once
#include "PacmanCore.h"

class GameGrid;
class World;
class GridCell;

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
	static std::shared_ptr<GameGrid> GenerateGrid(std::shared_ptr<World> ParentWorld, uint16_t Width, uint16_t Height, std::vector<CellContent> CellContents, std::vector<CellRule> CellRules);
	static void SpawnDot(std::shared_ptr<World> ParentWorld, std::shared_ptr<GridCell> ParentCell, Point2 Coordinate);
	static void SpawnCookie(std::shared_ptr<World> ParentWorld, std::shared_ptr<GridCell> ParentCell, Point2 Coordinate);
};

