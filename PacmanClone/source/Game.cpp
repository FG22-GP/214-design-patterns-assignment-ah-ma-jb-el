#include "PacmanCore.h"

// Game Entry
int main(int argc, char* argv[]){
	Application::Init();

	auto window = Window::Create(
		"Pack-Man Clone", 800, 600
	);
	while (window->IsOpened()){
		// Update Input
		// Update Actors

		window->StartDrawing();

		// Render Actors

		window->StopDrawing();
	}
	Application::Quit();
	return 0;
}