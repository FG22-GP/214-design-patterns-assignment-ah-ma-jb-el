#include "PacmanCore.h"
#include "Ghost_Anton.h"

#include "Grid/GridCell.h"
#include "Grid/GridCellContent.h"
#include "ZakuMan/ZakuMan.hpp"

Ghost_Anton::Ghost_Anton(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
    : IGhost(ParentWorld, StartTransform)
{
    std::vector<std::string> names;
    names.emplace_back("Ghost_1");
    names.emplace_back("Ghost_5");

    const auto sprite_1 = AssetLoader::GetSprite(names[0]);
    const auto sprite_2 = AssetLoader::GetSprite(names[1]);

    std::vector<std::shared_ptr<Sprite>> sprites;
    sprites.push_back(sprite_1);
    sprites.push_back(sprite_2);
    
    SpriteComp->Initialise(sprites);
}

Point2 Ghost_Anton::GetTargetCoord()
{
    //initial null-checks
    if (ZakuMan == nullptr || ZakuMan->GetCell() == nullptr)
        { return Point2{}; }
    
    return ZakuMan->GetCell()->Coordinate;
}
