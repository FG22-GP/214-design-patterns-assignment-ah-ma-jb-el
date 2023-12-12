#include "PacmanCore.h"
#include "Ghost_Johan.h"

#include "Ghost_Anton.h"
#include "Grid/GridCell.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"


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
    
    const Point2 targetVector = DirectionHelpers::GetPoint2InDirection(ZakuCoord, ZakuDir, 2) - FriendCoord;
    
    return targetVector + targetVector;
}
