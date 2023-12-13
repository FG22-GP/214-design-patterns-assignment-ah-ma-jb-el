#include "PacmanCore.h"
#include "GridGenerator.h"
#include "GameGrid.h"
#include "GridCell.h"
#include "GridLink.h"
#include "GridWrapLink.h"
#include "GridCellContent.h"
#include "World\World.hpp"
#include "PickUps\Dot.h"
#include "PickUps\Cookie.h"
#include "CellSpriteGenerator.h"
#include "SpriteMap.hpp"

std::shared_ptr<GameGrid> GridGenerator::GenerateGrid(std::shared_ptr<World> ParentWorld, uint16_t Width, uint16_t Height, std::vector<CellContent> CellContents, std::vector<CellRule> CellRules)
{
	std::shared_ptr<GameGrid> Grid = std::make_shared<GameGrid>(Width, Height);

	// Generate all cells with coordinates, walkable rules and spawn food content.
	for (int i = 0; i < Width * Height; i++)
	{
		std::shared_ptr<GridCell> NewCell = ParentWorld->CreateActor<GridCell>();
		Point2 Coordinate(i % Width, i / Width);
		NewCell->Coordinate = Coordinate;
		NewCell->ActorTransform.SetLocation(Coordinate);

		switch (CellRules[i])
		{
		case CR_Wall:
			break;
		case CR_Standard:
			NewCell->bIsPlayerWalkable = true;
			NewCell->bIsGhostWalkable = true;
			break;
		case CR_Ghost:
			NewCell->bIsPlayerWalkable = false; 
			NewCell->bIsGhostWalkable = true;
			break;
		case CR_GhostNoUp:
			NewCell->bIsPlayerWalkable = true;
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostCannotWalkUp = true;
			break;
		case CR_GhostSlow:
			NewCell->bIsPlayerWalkable = true;
			NewCell->bIsGhostWalkable = true;
			NewCell->bGhostIsSlowed = true;
			break;
		}

		std::cout << "Cell " << NewCell->Coordinate.ToString() << " is " << (NewCell->bIsPlayerWalkable ? "walkable" : "not walkable") << std::endl;
		
		

		Grid->Cells[i] = NewCell;

	}

	// Generate Links between cells. 
	// Note that they are ordered according to Point2::AllDirections()'s order of directions.
	for (int i = 0; i < Width * Height; i++)
	{
		Point2 Coord = Grid->Cells[i]->Coordinate;
		for (Point2 Direction : Point2::AllDirections())
		{
			Point2 NeighbourCoord = Coord + Direction;

			// Ugly vector modulo operations for wrapping the board's edges
			bool bIsEdge = true;
			if (NeighbourCoord.GetX() < 0)
				NeighbourCoord.SetX(NeighbourCoord.GetX() + Width);
			else if (NeighbourCoord.GetX() >= Width)
				NeighbourCoord.SetX(NeighbourCoord.GetX() - Width);
			else if (NeighbourCoord.GetY() < 0)
				NeighbourCoord.SetY(NeighbourCoord.GetY() + Height);
			else if (NeighbourCoord.GetY() >= Height)
				NeighbourCoord.SetY(NeighbourCoord.GetY() - Height);
			else
				bIsEdge = false;

			// If we're wrapping around the edge, we create a GridWrapLink instead of a regular GridLink.
			std::shared_ptr<GridLink> Link = bIsEdge ? std::make_shared<GridWrapLink>() : std::make_shared<GridLink>();

			Link->Source = Grid->Cells[i];
			Link->Target = Grid->GetCellAt(NeighbourCoord);
			Grid->Cells[i]->Links.push_back(Link);
		}
	}

	auto map = std::make_shared<SpriteMap>();
	CellSpriteGenerator::GenerateSpriteComponents(Grid, map);

	for (int i = 0; i < Width * Height; i++)
	{
		switch (CellContents[i])
		{
		case CC_Empty:
			break;
		case CC_Dot:
			SpawnDot(ParentWorld, Grid->Cells[i], Grid->Cells[i]->Coordinate);
			break;
		case CC_Cookie:
			SpawnCookie(ParentWorld, Grid->Cells[i], Grid->Cells[i]->Coordinate);
			break;
		case CC_Fruit:
			//TODO: Spawn Fruit
			break;
		}
	}

	return Grid;
}

void GridGenerator::SpawnDot(std::shared_ptr<World> ParentWorld, std::shared_ptr<GridCell> ParentCell, Point2 Coordinate)
{
	std::shared_ptr<Dot> NewDot = ParentWorld->CreateActor<Dot>();
	NewDot->ActorTransform.SetLocation(Coordinate);
	NewDot->ActorTransform.SetScale(Vector2::One());
	ParentCell->AddContent(NewDot);
	NewDot->SetCell(ParentCell);
	NewDot->BindToCell(ParentCell);

	std::shared_ptr<SpriteComponent> spriteComp = NewDot->AddComponent<SpriteComponent>();
	std::vector<std::string> names;
	names.emplace_back("Dot");
	const auto sprite = AssetLoader::GetSprite(names[0]);
	spriteComp->Initialize(sprite);
}

void GridGenerator::SpawnCookie(std::shared_ptr<World> ParentWorld, std::shared_ptr<GridCell> ParentCell, Point2 Coordinate)
{
	std::shared_ptr<Cookie> NewDot = ParentWorld->CreateActor<Cookie>();
	NewDot->ActorTransform.SetLocation(Coordinate);
	NewDot->ActorTransform.SetScale(Vector2::One());
	ParentCell->AddContent(NewDot);
	NewDot->SetCell(ParentCell);
	NewDot->BindToCell(ParentCell);

	std::shared_ptr<SpriteComponent> spriteComp = NewDot->AddComponent<SpriteComponent>();
	std::vector<std::string> names;
	names.emplace_back("Energizer");
	const auto sprite = AssetLoader::GetSprite(names[0]);
	spriteComp->Initialize(sprite);
}