#pragma once

#include "Core.hpp"

struct SDL_Renderer;

namespace GameEngine
{
	class Renderer
	{
	public:

		GAME_API static void StartDrawing();
		GAME_API static void StopDrawing();
		GAME_API static void Clean();

	private:

		struct Deleter { void operator()(SDL_Renderer*) const noexcept; };
		std::unique_ptr<SDL_Renderer, Deleter> m_Renderer;

		Renderer();
		Renderer(const Renderer&) = delete;
		void operator = (const Renderer&) = delete;

		static Renderer& GetInstance();

	};
}