#include "Core.hpp"
#include "Renderer.hpp"

namespace GameEngine
{
	SDL_Renderer* Renderer::s_Renderer;

// RENDERER
	
	void Renderer::StartDrawing(){
		SDL_RenderClear(s_Renderer);
	}

	void Renderer::StopDrawing(){
		SDL_RenderPresent(s_Renderer);
	}

	void Renderer::Clean(){
		SDL_DestroyRenderer(s_Renderer);
	}

}