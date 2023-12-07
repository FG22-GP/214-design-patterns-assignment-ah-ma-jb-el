#include "PacmanCore.h"
#include "PacmanGame.h"
#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "World\Actors\Actor.hpp"
#include "World\Actors\SpriteComponent.hpp"
#include "Game\PacmanLevelInfoParser.h"
#include "Engine\File\FileReader.hpp"
#include "Grid\GridGenerator.h"
#include "ZakuMan/ZakuMan.hpp"

void PacmanGame::Initialize()
{
	GameBase::Initialize();

	GameWorld = std::make_shared<World>();

	std::vector<std::string> CSVStrings = FileReader::ReadCSVFile("MapGenFiles/LevelInfo.txt");
	PacmanLevelInfo LevelInfo = PacmanLevelInfoParser::ParseFromStringVector(CSVStrings);
	
	std::shared_ptr<GameGrid> Grid;
	if (LevelInfo.bIsValid)
		Grid = GridGenerator::GenerateGrid(GameWorld, LevelInfo.Width, LevelInfo.Height, LevelInfo.Content, LevelInfo.Rules);
	
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

	/* ----ZAKU TEST STUFF ---- 
	std::shared_ptr<ZakuMan> Zaku = GameWorld->CreateActor<ZakuMan>();
	Zaku->ActorTransform.SetLocation(Vector2(1.5f, 1.5f));
	
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
	Zaku->GetSpriteComponent()->Initialize(TestSprite);
	*/
}

void PacmanGame::TEST_Tick(float DeltaTime)
{
	TestActor->ActorTransform.AddLocation(Vector2(1, 1) * DeltaTime);
}
