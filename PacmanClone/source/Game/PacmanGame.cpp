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
	LoadSprites();

	GameWorld = std::make_shared<World>();
	LoadLevel();
	
	if(LevelInfo.bIsValid)
	{
		// Create the player
		const std::shared_ptr<ZakuMan> Zaku = GameWorld->CreateActor<ZakuMan>();
		Zaku->ActorTransform.SetLocation(Vector2(1.5f, 1.5f));
		const Point2 PlayerSpawn = LevelInfo.PlayerSpawn;
		Grid->GetCellAt(PlayerSpawn)->AddContent(Zaku);
		Zaku->SetCell(Grid->GetCellAt(PlayerSpawn));
		Zaku->ActorTransform.SetLocation(PlayerSpawn);
		Zaku->GetMovementComponent()->Init(Grid->GetCellAt(PlayerSpawn));
	}

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

void PacmanGame::LoadSprites(){
	AssetLoader::LoadTexture(AssetLoader::GetAssetPath("SpriteAtlas.png"));
	auto atlas = AssetLoader::GetTexture("SpriteAtlas");

	std::vector<std::string> names(27);
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
	names[24] = "Ghost_5";
	names[25] = "Energizer";
	names[26] = "Dot";

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
}
