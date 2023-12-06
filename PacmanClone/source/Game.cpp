#include "PacmanCore.h"
#include "Game/PacmanGame.h"

// Game Entry
int main(int argc, char* argv[]){
	
	std::unique_ptr<PacmanGame> Game = std::make_unique<PacmanGame>();
	Game->Initialize();
	Game->Run();
	Game->Exit();
	return 0;
}