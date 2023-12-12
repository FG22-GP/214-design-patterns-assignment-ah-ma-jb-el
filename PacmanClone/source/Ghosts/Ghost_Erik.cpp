#include "PacmanCore.h"
#include "Ghost_Erik.h"

#include "Grid/GameGrid.h"
#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"


Ghost_Erik::Ghost_Erik(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
    : IGhost(ParentWorld, StartTransform)
{
    std::vector<std::string> names;
    names.emplace_back("Ghost_2");

    const auto sprite = AssetLoader::GetSprite(names[0]);

    SpriteComp->Initialize(sprite);
}

Point2 Ghost_Erik::GetTargetCoord()
{
    //initial null-checks
    if (ZakuMan == nullptr || ZakuMan->GetCell() == nullptr || ZakuMan->GetMovementComponent() == nullptr)
        { return Point2{}; }
    
    std::shared_ptr<GridCell> ZakuCell = ZakuMan->GetCell();
    Directions ZakuDir = ZakuMan->GetMovementComponent()->GetCurrentDirection();
    
    if (ZakuDir == None) { return Point2{}; }

    Point2 newCoord = DirectionHelpers::GetPoint2InDirection(ZakuCell->Coordinate, ZakuDir, 4);
    return newCoord;
}
