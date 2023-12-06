#pragma once

#include "Core.hpp"
#include <Engine/World/World.hpp>

namespace GameEngine
{
	class Window;

	class GameBase
	{
	public:
		GAME_API virtual void Initialize();
		GAME_API virtual void Run();
		GAME_API virtual void Exit();

	protected:
		std::unique_ptr<World> GameWorld;

	private:
		std::shared_ptr<Window> m_Window;

	};
}


