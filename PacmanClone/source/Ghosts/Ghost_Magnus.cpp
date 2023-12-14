#include "PacmanCore.h"
#include "Ghost_Magnus.h"

#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"
#include "Movement/Pathfinding.h"
#include "ZakuMan/ZakuMan.hpp"

Ghost_Magnus::Ghost_Magnus(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
    : IGhost(ParentWorld, StartTransform)
{
    std::vector<std::string> names;
    names.emplace_back("Ghost_4");
    names.emplace_back("Ghost_5");
    names.emplace_back("Ghost_Dead");

    const auto sprite_1 = AssetLoader::GetSprite(names[0]);
    const auto sprite_2 = AssetLoader::GetSprite(names[1]);
    const auto sprite_3 = AssetLoader::GetSprite(names[2]);


    std::vector<std::shared_ptr<Sprite>> sprites;
    sprites.push_back(sprite_1);
    sprites.push_back(sprite_2);
    sprites.push_back(sprite_3);

    
    SpriteComp->Initialise(sprites);
}

Point2 Ghost_Magnus::GetTargetCoord()
{
    //initial null-checks
    if (MovementComp == nullptr || ZakuMan == nullptr) { return Point2{}; }
    
    const std::shared_ptr<GridCell> startCell = MovementComp->GetTargetCell();
    std::shared_ptr<GridCell> targetCell = ZakuMan->GetCell();

    //secondary null-checks
    if (startCell == nullptr || targetCell  == nullptr) { return Point2{}; }
    
    const float distance = Pathfinding::Calculate_Distance(startCell, targetCell->Coordinate);
    
    if (distance > 8)
    {
        return targetCell->Coordinate;
    }

    return ScatterCellCoords;
}
