#include "PacmanCore.h"
#include "PacmanGame.h"
#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "World\Actors\Actor.hpp"
#include "World\Actors\SpriteComponent.hpp"
#include "Game\PacmanLevelInfoParser.h"
#include "Engine\File\FileReader.hpp"
#include "Grid/GameGrid.h"
#include "Grid/GridCellContent.h"
#include "Grid\GridGenerator.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"

void PacmanGame::Initialize()
{
	GameBase::Initialize();

	GameWorld = std::make_shared<World>();
	LoadSprites();
	LoadLevel();
	
	if(LevelInfo.bIsValid)
	{
		// Create the player
		const std::shared_ptr<ZakuMan> Zaku = GameWorld->CreateActor<ZakuMan>();
		Zaku->ActorTransform.SetLocation(Vector2(1.5f, 1.5f));
		const Point2 PlayerSpawn = LevelInfo.PlayerSpawn;
		Zaku->SetCell(Grid->GetCellAt(PlayerSpawn));
		Zaku->ActorTransform.SetLocation(PlayerSpawn);
		Zaku->GetMovementComponent()->Init(Grid->GetCellAt(PlayerSpawn));
	}

	
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

void PacmanGame::LoadSprites(){
	AssetLoader::LoadTexture(AssetLoader::GetAssetPath("SpriteAtlas.png"));
	auto atlas = AssetLoader::GetTexture("SpriteAtlas");

	std::vector<std::string> names(26);
	names[0] = "NW_Inner";
	names[1] = "Horizontal_Top";
	names[2] = "NE_Inner";
	names[3] = "SE_Outer";
	names[4] = "Horizontal_Bottom";
	names[5] = "SW_Outer";
	names[6] = "Zakuman_Closed";
	names[7] = "Zakuman_Opened";
	names[8] = "Vertical_Left";
	names[9] = "Empty";
	names[10] = "Vertical_Right";
	names[11] = "Vertical_Right2";
	names[12] = "Filled";
	names[13] = "Vertical_Left2";
	names[14] = "Ghost_1";
	names[15] = "Ghost_2";
	names[16] = "SW_Inner";
	names[17] = "Horizontal_Bottom2";
	names[18] = "SE_Inner";
	names[19] = "NE_Outer";
	names[20] = "Horizontal_Top2";
	names[21] = "NW_Outer";
	names[22] = "Ghost_3";
	names[23] = "Ghost_4";
	names[24] = "Energizer";
	names[25] = "Dot";

	AssetLoader::LoadSprites(atlas, names, 8, 8);
}

void PacmanGame::LoadLevel()
{
	// Load the level info from the file
	const std::vector<std::string> CSVStrings = FileReader::ReadCSVFile("MapGenFiles/LevelInfo.txt");
	LevelInfo = PacmanLevelInfoParser::ParseFromStringVector(CSVStrings);
	if (!LevelInfo.bIsValid)
	{
		throw std::runtime_error("Level info is invalid!");
	}
		
	// Generate the grid from the level info 
	Grid = GridGenerator::GenerateGrid(GameWorld, LevelInfo.Width, LevelInfo.Height, LevelInfo.Content, LevelInfo.Rules);

	// Create Textures for each cell type
	std::shared_ptr<Texture> WallTexture = std::make_shared<Texture>( 
		m_Window->GetRenderer(),
		"Sprites/TestBlueSquare.png"
	);

	std::shared_ptr<Texture> FloorTexture = std::make_shared<Texture>(
		m_Window->GetRenderer(),
		"Sprites/TestWhiteSquare.png"
	);

	// Create Sprites for each cell type
	std::shared_ptr<Sprite> WallSprite = std::make_shared<Sprite>(
		WallTexture,
		Rectangle(0, 0, WallTexture->GetWidth(), WallTexture->GetHeight()),
		Rectangle(0, 0, 0, 0),
		Point2(0, 0),
		RenderFlip::None,
		0.0f
	);

	std::shared_ptr<Sprite> FloorSprite = std::make_shared<Sprite>(
		FloorTexture,
		Rectangle(0, 0, FloorTexture->GetWidth(), FloorTexture->GetHeight()),
		Rectangle(0, 0, 0, 0),
		Point2(0, 0),
		RenderFlip::None,
		0.0f
	);

	// Loop through each cell, initialize a sprite component for it and set its location 
	for (const std::shared_ptr<GridCell> cell : Grid->Cells)
	{
		const std::shared_ptr<SpriteComponent> SpriteComp = cell->AddComponent<SpriteComponent>();
		if (cell->bIsPlayerWalkable)
			SpriteComp->Initialize(FloorSprite);
		else
			SpriteComp->Initialize(WallSprite);

		cell->ActorTransform.SetLocation(cell->Coordinate);
	}

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
