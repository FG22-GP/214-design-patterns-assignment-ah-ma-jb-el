#include "PacmanCore.h"
#include "PacmanGame.h"
#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "World\Actors\Actor.hpp"
#include "World\Actors\SpriteComponent.hpp"
#include "Game\PacmanLevelInfoParser.h"

void PacmanGame::Initialize()
{
	GameBase::Initialize();

	GameWorld = std::make_unique<World>();
	
	bUseTestFunctions = false;

	if (bUseTestFunctions)
		TEST_Init();
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
	if (bUseTestFunctions)
		TEST_Tick(DeltaTime);
}

void PacmanGame::HandleRendering()
{
	GameWorld->RenderAllRegisteredActors();
}

//This is test code to show how to make textures, sprites, actors and sprite components.
void PacmanGame::TEST_Init()
{
	std::shared_ptr<Texture> TestTexture = std::make_shared<Texture>(
		m_Window->GetRenderer(),
		TestPath
	);

	std::shared_ptr<Sprite> TestSprite = std::make_shared<Sprite>(
		TestTexture,
		Rectangle(0, 0, TestTexture->GetWidth(), TestTexture->GetHeight()),
		Rectangle(0, 0, 0, 0),
		Point2(0, 0),
		RenderFlip::None,
		0.0f
	);

	TestActor = GameWorld->CreateActor<Actor>();
	TestActor->ActorTransform.SetLocation(Vector2(0.5f, 0.5f));
	auto SpriteComp = TestActor->AddComponent<SpriteComponent>();
	SpriteComp->Initialize(TestSprite);

	//Grabs a test level info struct, just to check that it's valid
	PacmanLevelInfo Info = PacmanLevelInfoParser::GetTestLevelInfo();
}

void PacmanGame::TEST_Tick(float DeltaTime)
{
	TestActor->ActorTransform.AddLocation(Vector2(1, 1) * DeltaTime);
}
