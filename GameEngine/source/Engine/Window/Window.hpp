#pragma once

#include "Core.hpp"

struct SDL_Window;

namespace GameEngine
{
	struct Point2;
	class IRenderable;
	class Renderer;

	class Window
	{
		friend class Renderer;

	public:

	// STATES

		GAME_API bool IsOpened();

	// GETTERS

		GAME_API static std::shared_ptr<Window> GetMain();

		GAME_API std::shared_ptr<Renderer> GetRenderer() const;

		GAME_API Point2 GetSize() const;

	// WINDOW

		GAME_API static std::shared_ptr<Window> Create(
			const std::string& title, const uint32_t width, const uint32_t height
		);
		GAME_API void Update();
		GAME_API void StartDrawing();
		GAME_API void Draw(IRenderable& sprite);
		GAME_API void StopDrawing();
		GAME_API void Close();

	// OPERATORS

		GAME_API operator SDL_Window* ();

	private:

		bool m_IsOpened;

		std::shared_ptr<Renderer> m_renderer;

		struct Deleter { void operator()(SDL_Window*) const noexcept; };
		std::unique_ptr<SDL_Window, Deleter> m_Window;

		static std::shared_ptr<Window> s_Main;

	// CONSTRUCTORS

		Window(const std::string& title, const uint32_t width, const uint32_t height);

	};
}