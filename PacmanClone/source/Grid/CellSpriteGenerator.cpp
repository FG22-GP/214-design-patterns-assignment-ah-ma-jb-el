#include "PacmanCore.h"
#include "CellSpriteGenerator.h"
#include "Grid\GameGrid.h"
#include "Grid\GridCell.h"
#include "World\Actors\SpriteComponent.hpp"


void CellSpriteGenerator::GenerateSpriteComponents(std::shared_ptr<GameGrid> Grid, std::shared_ptr <IAlignedSpriteMap> SpriteMap)
{
	for (auto Cell : Grid->Cells)
	{
		HandleCell(Cell, SpriteMap);
	}
}

void CellSpriteGenerator::HandleCell(std::shared_ptr<GridCell> Cell, std::shared_ptr <IAlignedSpriteMap> SpriteMap)
{
	GameEngine::CellSpriteAlignment Alignment = GetCellAlignment(Cell);

	std::shared_ptr<Sprite> AlignedSprite = SpriteMap->GetAlignedSprite(Alignment);

	std::shared_ptr<SpriteComponent> SpriteComp = Cell->AddComponent<SpriteComponent>();
	SpriteComp->Initialize(AlignedSprite);
}

CellSpriteAlignment CellSpriteGenerator::GetCellAlignment(std::shared_ptr<GridCell> Cell)
{
	if (Cell->bIsPlayerWalkable)
		return CellSpriteAlignment::Empty;

	//Index ordering, powers of 2: Up = 1, Down = 2; Right = 4, Left = 8
	int Walkability = 0;
	for (int i = 0; i < 4; i++)
	{
		if (Cell->Links[i]->Target->bIsPlayerWalkable)
			Walkability += 2 ^ i;
	}

	switch (Walkability)
	{
		//Cases with 1 walkable neighbour
	case 1:
		return Horizontal_Top;
	case 2:
		return Horizontal_Bottom;
	case 4:
		return Vertical_Right;
	case 8:
		return Vertical_Left;

		//Cases with 2 walkable neighbours
	case 5:
		return NE_Outer;
	case 6:
		return SE_Outer;
	case 9:
		return NW_Outer;
	case 10:
		return SW_Outer;

	case 0:
		//special case, handled outside of switch case
		break;

	//Impossible cases
	default:
		return NONE;
	};

	//At this point we know that our cell is a wall tile with no walkable neighbours.
	//We need to check if it should be a full solid, or an inner corner.
	bool NEWalkable = Cell->Links[0]->Target->Links[2]->Target->bIsPlayerWalkable;
	bool NWWalkable = Cell->Links[0]->Target->Links[3]->Target->bIsPlayerWalkable;
	bool SEWalkable = Cell->Links[1]->Target->Links[2]->Target->bIsPlayerWalkable;
	bool SWWalkable = Cell->Links[1]->Target->Links[3]->Target->bIsPlayerWalkable;

	if (NEWalkable)
		return NE_Inner;
	if (NWWalkable)
		return NW_Inner;
	if (SEWalkable)
		return SE_Inner;
	if (SWWalkable)
		return SW_Inner;

	return Filled;
}
