#include "PacmanCore.h"
#include "ZakuMan.hpp"

#include "Engine/Input/Input.hpp"
#include "Movement/MovementComponent.h"
#include "World/Actors/SpriteAnimationComponent.hpp"
#include "World/Actors/SpriteComponent.hpp"


ZakuMan::ZakuMan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform)
    : Actor(ParentWorld, StartTransform)
{
    MoveComp = AddComponent<MovementComponent>();

    // Register Input Events
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::W, [this] { MoveComp->SetDirection(Up); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::A, [this] { MoveComp->SetDirection(Left); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::S, [this] { MoveComp->SetDirection(Down); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::D, [this] { MoveComp->SetDirection(Right); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::ArrowUp, [this] { MoveComp->SetDirection(Up); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::ArrowLeft, [this] { MoveComp->SetDirection(Left); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::ArrowDown, [this] { MoveComp->SetDirection(Down); });
    Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::ArrowRight, [this] { MoveComp->SetDirection(Right); });

    std::vector<std::shared_ptr<Sprite>> sprites{
        AssetLoader::GetSprite("Zakuman_Closed"),
        AssetLoader::GetSprite("Zakuman_Opened")
    };
    auto AnimComp = AddComponent<SpriteAnimationComponent>();
         AnimComp->Initialise(sprites, 0.5f);

    SpriteComp = AnimComp;
}

