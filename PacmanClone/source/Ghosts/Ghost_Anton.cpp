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

    const auto sprite = AssetLoader::GetSprite(names[0]);

    SpriteComp->Initialize(sprite);
}

Point2 Ghost_Anton::GetTargetCoord()
{
    //initial null-checks
    if (ZakuMan == nullptr || ZakuMan->GetCell() == nullptr)
        { return Point2{}; }
    
    return ZakuMan->GetCell()->Coordinate;
}
