#include "PacmanCore.h"
#include "PacmanGame.h"
#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "World\Actors\Actor.hpp"
#include "World\Actors\SpriteComponent.hpp"

void PacmanGame::Initialize()
{
	GameBase::Initialize();

	GameWorld = std::make_unique<World>();

	/* This is test code to show how to make textures, sprites, actors and sprite components.
	std::shared_ptr<Texture> TestTexture = std::make_shared<Texture>(
		m_Window->GetRenderer(),
		"C:/Users/lunne/Desktop/Unreal Projects/214-design-patterns-assignment-ah-ma-jb-el/PacmanClone/Sprites/TestSprite.png"
	);

	std::shared_ptr<Sprite> TestSprite = std::make_shared<Sprite>(
		TestTexture,
		Rectangle(0, 0, TestTexture->GetWidth(), TestTexture->GetHeight()),
		Rectangle(0, 0, 0, 0),
		Point2(0, 0),
		RenderFlip::None,
		0.0f
	);

	std::shared_ptr<Actor> TestActor = GameWorld->CreateActor<Actor>();
	TestActor->ActorTransform.SetLocation(Vector2(5, 5));
	auto SpriteComp = TestActor->AddComponent<SpriteComponent>();
	SpriteComp->Initialize(TestSprite);*/
}

void PacmanGame::Run()
{
	GameBase::Run();
}

void PacmanGame::Exit()
{
	GameBase::Exit();
}

void PacmanGame::HandleTick(float DeltaTime)
{
	GameWorld->Tick(DeltaTime);
}

void PacmanGame::HandleRendering()
{
	GameWorld->RenderAllRegisteredActors();
}
