#pragma once

#include "Core.hpp"

namespace GameEngine
{
	class Window;

	class GameBase
	{
	public:
		GAME_API virtual void Initialize();
		GAME_API virtual void Run();
		GAME_API virtual void Exit();
		GAME_API virtual void HandleTick(float DeltaTime) {}
		GAME_API virtual void HandleRendering() {}

	protected:
		std::shared_ptr<Window> m_Window;

	};
}


