#include "PacmanCore.h"

// Game entry
int main(int argc, char* argv[]){
	Application::Init();

	Window::Create("Packman Clone", 800, 600);

	while (Window::IsOpened()){
		Renderer::StartDrawing();

		// Render objects

		Renderer::StopDrawing();
	}
	Window::Clean();
	Renderer::Clean();

	Application::Quit();
	return 0;
}