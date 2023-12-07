#include "PacmanCore.h"
#include "ZakuMan.hpp"
#include "Movement/MovementComponent.h"
#include "Grid/GridCellContent.h"
#include "World/Actors/SpriteComponent.hpp"


ZakuMan::ZakuMan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
    : Actor(ParentWorld, StartTransform) {
    MoveComp = AddComponent<MovementComponent>();
    SpriteComp = AddComponent<SpriteComponent>();
    
    CellContent = std::make_shared<GridCellContent>();

    std::cout << "ZakuMan::ZakuMan" << std::endl;
}