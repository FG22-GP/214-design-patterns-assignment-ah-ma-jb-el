#include "PacmanCore.h"
#include "PacmanGame.h"
#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "Engine/World/Actors/Actor.hpp"
#include "Engine/World/World.hpp"
#include "Engine/World/Actors/SpriteComponent.hpp"

void PacmanGame::Initialize()
{
	GameBase::Initialize();
	/*
	std::shared_ptr<Texture> TestTexture = std::make_shared<Texture>(
		m_Window->GetRenderer(),
		"C:/Users/anton.hedlund/UnrealProjects/214-design-patterns-assignment-ah-ma-jb-el/PacmanClone/Sprites/TestSprite.png"
	);

	std::shared_ptr<Sprite> TestSprite = std::make_shared<Sprite>(
		TestTexture,
		Rectangle(0, 0, TestTexture->GetWidth(), TestTexture->GetHeight()),
		Rectangle(0, 0, 0, 0),
		Point2(0, 0),
		RenderFlip::None,
		0.0f
	);

	auto TestActor = GameWorld->CreateActor<Actor>();
	TestActor->AddComponent<SpriteComponent>();
	*/
}

void PacmanGame::Run()
{
	GameBase::Run();
}

void PacmanGame::Exit()
{
	GameBase::Exit();
}
