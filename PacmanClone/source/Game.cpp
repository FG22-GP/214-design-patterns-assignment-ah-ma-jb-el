#include "PacmanCore.h"
#include "Game/PacmanGame.h"

#if defined _DEBUG
int main(int argc, char* argv[]){ // Debug console application
#else
int WinMain(int argc, char* argv[]){ // Windows application
#endif	
	std::unique_ptr<PacmanGame> Game = std::make_unique<PacmanGame>();
	Game->Initialize();
	Game->Run();
	Game->Exit();
	return 0;
}