#pragma once

#include "PacmanCore.h"
#include "GridLink.h"
#include "World\Actors\Actor.hpp"

class GridCellContent;
class GameGrid;

class GridCell : public Actor
{

public:
	GridCell(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) :
		Actor(ParentWorld, StartTransform) {}

	void Initialize(std::shared_ptr<GameGrid> ParentGrid);
	
	bool bIsPlayerWalkable = false;
	bool bIsGhostWalkable = false;
	bool bGhostCannotWalkUp = false;
	bool bGhostIsSlowed = false;
	
	//Use Directions from Point2.hpp to keep track of indices
	std::vector<std::shared_ptr<GridLink>> Links;

	std::shared_ptr<GridLink> GetLinkInDirection(GameEngine::Directions Direction);

	//These are all objects currently within the cell. Food, player, ghosts.
	std::vector<std::shared_ptr<GridCellContent>> Contents;

	//Reference to and coordinate within parent Grid.
	std::shared_ptr<GameGrid> Grid;
	Point2 Coordinate;
};

