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
#include <PickUps\Dot.h>

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

	SetupWinCon();

}

void PacmanGame::Run()
{
	GameBase::Run();
}

void PacmanGame::Exit()
{
	EventBroker::OnDotEaten.RemoveListener(Callback);

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

	std::vector<std::string> names {
		"NW_Inner",
		"Horizontal_Top",
		"NE_Inner",
		"SE_Outer",
		"Horizontal_Bottom",
		"SW_Outer",
		"Zakuman_Closed",
		"Zakuman_Opened",
		"Vertical_Left",
		"Empty",
		"Vertical_Right",
		"Vertical_Right2",
		"Filled",
		"Vertical_Left2",
		"Ghost_1",
		"Ghost_2",
		"SW_Inner",
		"Horizontal_Bottom2",
		"SE_Inner",
		"NE_Outer",
		"Horizontal_Top2",
		"NW_Outer",
		"Ghost_3",
		"Ghost_4",
		"Ghost_5",
		"Ghost_Dead",
		"Energizer",
		"Dot",
	};
	AssetLoader::LoadSprites(atlas, names, 8, 8);
	AssetLoader::LoadSprite(atlas, "Won",  0, 4, 4, 4, 8, 8);
	AssetLoader::LoadSprite(atlas, "Lost", 4, 4, 4, 4, 8, 8);
}

void PacmanGame::LoadLevel()
{
	// Load the level info from the file
	const std::vector<std::string> CSVStrings = FileReader::ReadCSVFile(
		AssetLoader::GetAssetPath("LevelInfo.txt")
	);
	LevelInfo = PacmanLevelInfoParser::ParseFromStringVector(CSVStrings);
	if (!LevelInfo.bIsValid)
	{
		throw std::runtime_error("Level info is invalid!");
	}
		
	// Generate the grid from the level info 
	Grid = GridGenerator::GenerateGrid(GameWorld, LevelInfo.Width, LevelInfo.Height, LevelInfo.Content, LevelInfo.Rules);
}

void PacmanGame::SetupWinCon()
{
	if (Dot::TotalDots < 1) return;

	Callback = EventBroker::OnDotEaten.AddListener(
		[this]() {
			this->HandleDotEaten();
		});
}

void PacmanGame::HandleDotEaten()
{
	EatenDots++;
	std::cout << "You've eaten " << EatenDots << " Dots out of " << Dot::TotalDots << "." << std::endl;
	if (EatenDots >= Dot::TotalDots)
	{
		GameWorld->bShouldTickActors = false;
		std::cout << "WinCon here" << std::endl;
	}
}

std::shared_ptr<ZakuMan> PacmanGame::SpawnPlayer() const
{
	// Create the player
	std::shared_ptr<ZakuMan> Zaku = GameWorld->CreateActor<ZakuMan>();
	const Point2 PlayerSpawn = LevelInfo.PlayerSpawn;
	Grid->GetCellAt(PlayerSpawn)->AddContent(Zaku);
	Zaku->SetCell(Grid->GetCellAt(PlayerSpawn));
	Zaku->ActorTransform.SetLocation(PlayerSpawn);
	Zaku->GetMovementComponent()->Init(Grid->GetCellAt(PlayerSpawn), true);
	return Zaku;
}

void PacmanGame::SpawnGhosts(std::shared_ptr<ZakuMan> Player) const
{
	const Point2 DeathCellCoords = Point2(12, 14);
	// Anton
	const std::shared_ptr<Ghost_Anton> Anton = GameWorld->CreateActor<Ghost_Anton>();
	const Point2 Ghost1Spawn = LevelInfo.GhostSpawn[0];
	Anton->ActorTransform.SetLocation(Ghost1Spawn);
	Grid->GetCellAt(Ghost1Spawn)->AddContent(Anton);
	Anton->SetCell(Grid->GetCellAt(Ghost1Spawn));
	Anton->GetMovementComponent()->Init(Grid->GetCellAt(Ghost1Spawn));
	Anton->InitializeGhost(DeathCellCoords, Point2(1, 1), Player);
	// Erik
	const std::shared_ptr<Ghost_Erik> Erik = GameWorld->CreateActor<Ghost_Erik>();
	const Point2 Ghost2Spawn = LevelInfo.GhostSpawn[1];
	Erik->ActorTransform.SetLocation(Ghost2Spawn);
	Grid->GetCellAt(Ghost2Spawn)->AddContent(Erik);
	Erik->SetCell(Grid->GetCellAt(Ghost2Spawn));
	Erik->GetMovementComponent()->Init(Grid->GetCellAt(Ghost2Spawn));
	Erik->InitializeGhost(DeathCellCoords, Point2(25, 25), Player);
	// Johan
	const std::shared_ptr<Ghost_Johan> Johan = GameWorld->CreateActor<Ghost_Johan>();
	const Point2 JohanSpawn = LevelInfo.GhostSpawn[2];
	Johan->ActorTransform.SetLocation(JohanSpawn);
	Grid->GetCellAt(JohanSpawn)->AddContent(Johan);
	Johan->SetCell(Grid->GetCellAt(JohanSpawn));
	Johan->GetMovementComponent()->Init(Grid->GetCellAt(JohanSpawn));
	Johan->InitializeGhost(DeathCellCoords, Point2(1, 25), Player);
	Johan->GiveFriend(Anton);
	// Magnus
	const std::shared_ptr<Ghost_Magnus> Magnus = GameWorld->CreateActor<Ghost_Magnus>();
	const Point2 MagnusSpawn = LevelInfo.GhostSpawn[3];
	Magnus->ActorTransform.SetLocation(MagnusSpawn);
	Grid->GetCellAt(MagnusSpawn)->AddContent(Magnus);
	Magnus->SetCell(Grid->GetCellAt(MagnusSpawn));
	Magnus->GetMovementComponent()->Init(Grid->GetCellAt(MagnusSpawn));
	Magnus->InitializeGhost(DeathCellCoords, Point2(25, 1), Player);
}
