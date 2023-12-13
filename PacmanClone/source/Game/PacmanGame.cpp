#include "PacmanCore.h"
#include "PacmanGame.h"
#include "World/Actors/Actor.hpp"
#include "Game/PacmanLevelInfoParser.h"
#include "Engine/File/FileReader.hpp"
#include "Ghosts/Ghost_Anton.h"
#include "Ghosts/Ghost_Erik.h"
#include "Ghosts/Ghost_Johan.h"
#include "Ghosts/Ghost_Magnus.h"
#include "Grid/GameGrid.h"
#include "Grid/GridCellContent.h"
#include "Grid/GridGenerator.h"
#include "Movement/MovementComponent.h"
#include "ZakuMan/ZakuMan.hpp"

void PacmanGame::Initialize()
{
	GameBase::Initialize();
	LoadSprites();

	GameWorld = std::make_shared<World>();
	LoadLevel();

	Input::RegisterInputEvent(KEY_DOWN_EVENT, KeyboardKey::Escape, [this]() { Exit(); });

	
	if(LevelInfo.bIsValid)
	{
		const std::shared_ptr<ZakuMan> Player = SpawnPlayer();
		SpawnGhosts(Player);
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

std::shared_ptr<ZakuMan> PacmanGame::SpawnPlayer() const
{
	// Create the player
	std::shared_ptr<ZakuMan> Zaku = GameWorld->CreateActor<ZakuMan>();
	const Point2 PlayerSpawn = LevelInfo.PlayerSpawn;
	Grid->GetCellAt(PlayerSpawn)->AddContent(Zaku);
	Zaku->SetCell(Grid->GetCellAt(PlayerSpawn));
	Zaku->ActorTransform.SetLocation(PlayerSpawn);
	Zaku->GetMovementComponent()->Init(Grid->GetCellAt(PlayerSpawn));
	return Zaku;
}

void PacmanGame::SpawnGhosts(std::shared_ptr<ZakuMan> Player) const
{
	// Anton
	const std::shared_ptr<Ghost_Anton> Anton = GameWorld->CreateActor<Ghost_Anton>();
	const Point2 Ghost1Spawn = LevelInfo.GhostSpawn[0];
	Anton->ActorTransform.SetLocation(Ghost1Spawn);
	Grid->GetCellAt(Ghost1Spawn)->AddContent(Anton);
	Anton->SetCell(Grid->GetCellAt(Ghost1Spawn));
	Anton->GetMovementComponent()->Init(Grid->GetCellAt(Ghost1Spawn));
	Anton->InitializeGhost(Point2(1,1), Point2(1, 1), Player);
	// Erik
	const std::shared_ptr<Ghost_Erik> Erik = GameWorld->CreateActor<Ghost_Erik>();
	const Point2 Ghost2Spawn = LevelInfo.GhostSpawn[1];
	Erik->ActorTransform.SetLocation(Ghost2Spawn);
	Grid->GetCellAt(Ghost2Spawn)->AddContent(Erik);
	Erik->SetCell(Grid->GetCellAt(Ghost2Spawn));
	Erik->GetMovementComponent()->Init(Grid->GetCellAt(Ghost2Spawn));
	Erik->InitializeGhost(Point2(1, 1), Point2(25, 25), Player);
	// Johan
	const std::shared_ptr<Ghost_Johan> Johan = GameWorld->CreateActor<Ghost_Johan>();
	const Point2 JohanSpawn = LevelInfo.GhostSpawn[2];
	Johan->ActorTransform.SetLocation(JohanSpawn);
	Grid->GetCellAt(JohanSpawn)->AddContent(Johan);
	Johan->SetCell(Grid->GetCellAt(JohanSpawn));
	Johan->GetMovementComponent()->Init(Grid->GetCellAt(JohanSpawn));
	Johan->InitializeGhost(Point2(1, 1), Point2(1, 25), Player);
	Johan->GiveFriend(Anton);
	// Magnus
	const std::shared_ptr<Ghost_Magnus> Magnus = GameWorld->CreateActor<Ghost_Magnus>();
	const Point2 MagnusSpawn = LevelInfo.GhostSpawn[3];
	Magnus->ActorTransform.SetLocation(MagnusSpawn);
	Grid->GetCellAt(MagnusSpawn)->AddContent(Magnus);
	Magnus->SetCell(Grid->GetCellAt(MagnusSpawn));
	Magnus->GetMovementComponent()->Init(Grid->GetCellAt(MagnusSpawn));
	Magnus->InitializeGhost(Point2(1, 1), Point2(25, 1), Player);
}
