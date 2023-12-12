#pragma once

#include "PacmanCore.h"
#include "GridLink.h"
#include "World\Actors\Actor.hpp"
#include "Event\Event.h"

class GridCellContent;
class GameGrid;

class GridCell : public Actor
{

public:
	GridCell(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform) :
		Actor(ParentWorld, StartTransform) {}

#pragma region Events
	Event<std::shared_ptr<GridCellContent>> OnContentEnters;
	Event<std::shared_ptr<GridCellContent>> OnContentExit;
#pragma endregion

	std::vector<std::shared_ptr<GridCellContent>> GetContents() const { return Contents; }
	void AddContent(const std::shared_ptr<GridCellContent> NewContent) 
	{ 
		Contents.push_back(NewContent); 
		OnContentEnters.Invoke(NewContent);
	}
	void RemoveContent(const std::shared_ptr<GridCellContent>& ContentToRemove)
	{
		auto it = std::find(Contents.begin(), Contents.end(), ContentToRemove);
		if (it != Contents.end()) {
			OnContentExit.Invoke(*it);
			Contents.erase(it);
		}
	}

	void Initialize(std::shared_ptr<GameGrid> ParentGrid);
	
	bool bIsPlayerWalkable = false;
	bool bIsGhostWalkable = false;
	bool bGhostCannotWalkUp = false;
	bool bGhostIsSlowed = false;
	
	//Use Directions from Point2.hpp to keep track of indices
	std::vector<std::shared_ptr<GridLink>> Links;

	std::shared_ptr<GridLink> GetLinkInDirection(GameEngine::Directions Direction);


	//Reference to and coordinate within parent Grid.
	std::shared_ptr<GameGrid> Grid;
	Point2 Coordinate;

private:
	//These are all objects currently within the cell. Food, player, ghosts.
	std::vector<std::shared_ptr<GridCellContent>> Contents;
};

