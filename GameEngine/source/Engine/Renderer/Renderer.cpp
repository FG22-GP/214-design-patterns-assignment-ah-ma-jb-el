#include "Core.hpp"
#include "Renderer.hpp"

#include "SDL.h"

namespace GameEngine
{
// SINGLETON

	Renderer& Renderer::GetInstance(){
		static Renderer instance;
		return instance;
	}

// CONSTRUCTORS

	Renderer::Renderer() :
		m_Renderer(nullptr){}

// RENDERER
	
	void Renderer::StartDrawing(){
		auto& instance = GetInstance();
		
		SDL_RenderClear(
			instance.m_Renderer.get()
		);
	}

	void Renderer::StopDrawing(){
		auto& instance = GetInstance();

		SDL_RenderPresent(
			instance.m_Renderer.get()
		);
	}

	void Renderer::Clean(){
		auto& instance = GetInstance();
		
		SDL_DestroyRenderer(
			instance.m_Renderer.get()
		);
		instance.m_Renderer = nullptr;
	}

// OPERATORS

	void Renderer::Deleter::operator()(SDL_Renderer* r) const noexcept { delete(r); }

}