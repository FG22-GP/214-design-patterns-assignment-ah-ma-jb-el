#include "PacmanCore.h"
#include "Ghost_Johan.h"

#include "Ghost_Anton.h"
#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"


Ghost_Johan::Ghost_Johan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
    : IGhost(ParentWorld, StartTransform)
{
    std::vector<std::string> names;
    names.emplace_back("Ghost_3");
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

void Ghost_Johan::GiveFriend(const std::shared_ptr<Ghost_Anton>& friendly)
{
    //give Johan a friend
    if (friendly != nullptr) { Friend = friendly; }
}

Point2 Ghost_Johan::GetTargetCoord()
{
    //a lot of null-checks
    if (ZakuMan == nullptr || ZakuMan->GetCell() == nullptr || ZakuMan->GetMovementComponent() == nullptr || Friend == nullptr || Friend->GetCell() == nullptr)
        { return Point2{}; }

    const Point2 ZakuCoord = ZakuMan->GetCell()->Coordinate;
    const Point2 FriendCoord = Friend->GetCell()->Coordinate;
    Directions ZakuDir = ZakuMan->GetMovementComponent()->GetCurrentDirection();
    
    if (ZakuDir == None) { return Point2{}; }
    
    const Point2 targetVector = Point2::GetPoint2InDirection(ZakuCoord, ZakuDir, 2) - FriendCoord;
    
    return targetVector + targetVector;
}
