#include "Core.hpp"
#include "Renderer.hpp"

#include "Interfaces/IRenderable.h"
#include "Data/Vectors/Point2.hpp"
#include "Data/Visuals/Texture.hpp"
#include "Data/Bounds/Rectangle.hpp"
#include "Engine/Window/Window.hpp"
#include "Data/Enums/RenderFlip.hpp"
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

		CameraSize = Vector2(28, 31);
		CameraTopLeftLocation = Vector2(-0.5f, -0.5f);
	}

// GETTERS

	Point2 Renderer::GetResolution() const {
		return Point2(
			m_Resolution->GetX(),
			m_Resolution->GetY()
		);
	}

// SETTINGS

	void Renderer::SetResolution(const uint32_t width, const uint32_t height){
		m_Resolution->SetX(width);
		m_Resolution->SetY(height);
	}

	void Renderer::SetResolution(const Point2& resolution){
		SetResolution(resolution.GetX(), resolution.GetY());
	}


	void Renderer::SetDrawColour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a){
		SDL_SetRenderDrawColor(
			m_Renderer.get(),
			r, g, b, a
		);
	}

	void Renderer::SetCameraProperties(const Vector2& CameraSize, const Vector2& TopLeftLocation)
	{
		this->CameraSize = CameraSize;
		this->CameraTopLeftLocation = TopLeftLocation;
	}

// RENDERING

	void Renderer::StartDrawing(){
		SDL_RenderClear(
			m_Renderer.get()
		);
	}

	void Renderer::Draw(IRenderable& render){
		Rectangle rect = GetScreenRectFromWorldLocation(render.GetWorldLocation(), render.GetWorldScale());
		Point2 centre = Point2(rect.GetWidth() / 2, rect.GetHeight() / 2);
		
		SDL_RenderCopyEx(
			m_Renderer.get(),
			render.GetTexture().ToSDL(),
			render.GetCrop().ToSDL(),
			rect.ToSDL(),
			render.GetRotation(),
			centre.ToSDL(),
			(SDL_RendererFlip)render.GetFlip()
		);

		//Here we check if a rect extends beyond the edge of the screen; in which case we wrap it.
		if (rect.GetX() < 0)
		{
			rect.SetX(rect.GetX() + m_Resolution.get()->GetX());
			SDL_RenderCopyEx(
				m_Renderer.get(),
				render.GetTexture().ToSDL(),
				render.GetCrop().ToSDL(),
				rect.ToSDL(),
				render.GetRotation(),
				centre.ToSDL(),
				(SDL_RendererFlip)render.GetFlip()
			);
		}
		else if (rect.GetX() + rect.GetWidth() > m_Resolution.get()->GetX())
		{
			rect.SetX(rect.GetX() - m_Resolution.get()->GetX());
			SDL_RenderCopyEx(
				m_Renderer.get(),
				render.GetTexture().ToSDL(),
				render.GetCrop().ToSDL(),
				rect.ToSDL(),
				render.GetRotation(),
				centre.ToSDL(),
				(SDL_RendererFlip)render.GetFlip()
			);
		}
	}

	void Renderer::StopDrawing(){
		SDL_RenderPresent(
			m_Renderer.get()
		);
	}

	Rectangle Renderer::GetScreenRectFromWorldLocation(const Vector2& WorldCenter, const Vector2& WorldScale) const
	{
		if (m_Resolution == nullptr || CameraSize.X == 0 || CameraSize.Y == 0)
			return Rectangle(0, 0, 0, 0);

		//Gives X=[0-1] and Y=[0-1] describing screen position for top left corner.
		Vector2 TopLeftNormalized = Vector2::InverseLerpByAxis(
			CameraTopLeftLocation,
			CameraTopLeftLocation + CameraSize,
			WorldCenter - WorldScale / 2.0f
		);

		//Uses the window resolution to determine pixel position, width and height
		return Rectangle(
			static_cast<uint32_t>(m_Resolution.get()->GetX() * TopLeftNormalized.X),
			static_cast<uint32_t>(m_Resolution.get()->GetY() * TopLeftNormalized.Y),
			static_cast<uint32_t>(m_Resolution.get()->GetX() * WorldScale.X / CameraSize.X),
			static_cast<uint32_t>(m_Resolution.get()->GetY() * WorldScale.Y / CameraSize.Y));
	}

// OPERATORS

	Renderer::operator SDL_Renderer* (){ return m_Renderer.get(); }

	


// OPERATORS

	void Renderer::ResDeleter::operator()(Point2* res) const noexcept { delete(res); }
	
	void Renderer::RendererDeleter::operator()(SDL_Renderer* r) const noexcept { 
		SDL_DestroyRenderer(r);
	}

}