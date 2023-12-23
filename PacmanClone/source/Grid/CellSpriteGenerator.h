#pragma once

#include "PacmanCore.h"
#include "Data\Visuals\Interfaces\IAlignedSpriteMap.hpp"

class GameGrid;
class GridCell;

class CellSpriteGenerator
{
public:

	static void GenerateSpriteComponents(std::shared_ptr<GameGrid> Grid, std::shared_ptr <IAlignedSpriteMap> SpriteMap);

private:

	static void HandleCell(std::shared_ptr<GridCell> Cell, std::shared_ptr <IAlignedSpriteMap> SpriteMap);
	static GameEngine::CellSpriteAlignment GetCellAlignment(std::shared_ptr<GridCell> Cell);

};

