#include "Core.hpp"
#include "Renderer.hpp"

#include "Data/Vectors/Point2.hpp"
#include "Engine/Window/Window.hpp"
#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Renderer::Renderer(const Window& window){
		auto* renderer = SDL_CreateRenderer(
			window.m_Window.get(),
			0, 
			0 //SDL_HINT_RENDER_VSYNC
		);
		m_Renderer.reset(renderer);

		m_Resolution.reset(
			new Point2(window.GetSize())
		);
	}

// GETTERS

	Point2 Renderer::GetResolution() const {
		return Point2(
			m_Resolution->x,
			m_Resolution->y
		);
	}

// SETTINGS

	void Renderer::SetResolution(const uint32_t width, const uint32_t height){
		m_Resolution->x = width;
		m_Resolution->y = height;
	}

	void Renderer::SetResolution(const Point2& resolution){
		SetResolution(resolution.x, resolution.y);
	}


	void Renderer::SetDrawColour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a){
		SDL_SetRenderDrawColor(
			m_Renderer.get(),
			r, g, b, a
		);
	}

// RENDERING

	void Renderer::StartDrawing(){
		SDL_RenderClear(
			m_Renderer.get()
		);
	}

	void Renderer::StopDrawing(){
		SDL_RenderPresent(
			m_Renderer.get()
		);
	}

// OPERATORS

	void Renderer::ResDeleter::operator()(Point2* res) const noexcept { delete(res); }
	
	void Renderer::RendererDeleter::operator()(SDL_Renderer* r) const noexcept { 
		SDL_DestroyRenderer(r);
	}

}