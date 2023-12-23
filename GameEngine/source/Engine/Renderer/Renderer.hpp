#pragma once

#include "Core.hpp"
#include "Data/Vectors/Vector2.hpp"

struct SDL_Renderer;

namespace GameEngine
{
	class IRenderable;
	struct Point2;
	class Window;
	struct Rectangle;

	class Renderer
	{
	public:

		GAME_API Renderer(const Window& window);

	// GETTERS
	
		GAME_API Point2 GetResolution() const;

	// SETTERS

		GAME_API void SetResolution(const uint32_t width, const uint32_t height);
		GAME_API void SetResolution(const Point2& resolution);

		GAME_API void SetDrawColour(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

		GAME_API void SetCameraProperties(const Vector2& CameraSize, const Vector2& BottomLeftLocation);

	// RENDERER

		GAME_API void StartDrawing();
		GAME_API void Draw(IRenderable& render);
		GAME_API void StopDrawing();

	// OPERATIONS

		GAME_API operator SDL_Renderer* ();

	private:

		struct ResDeleter { void operator()(Point2*) const noexcept; };
		std::unique_ptr<Point2, ResDeleter> m_Resolution;

		struct RendererDeleter { void operator()(SDL_Renderer*) const noexcept; };
		std::unique_ptr<SDL_Renderer, RendererDeleter> m_Renderer;

		Vector2 CameraSize;
		Vector2 CameraTopLeftLocation;

		Rectangle GetScreenRectFromWorldLocation(const Vector2& WorldCenter, const Vector2& WorldScale) const;

	};
}