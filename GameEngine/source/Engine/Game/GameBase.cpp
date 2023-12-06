#include "Core.hpp"
#include "GameBase.h"
#include "Engine/Application/Application.hpp"
#include "Engine/Window/Window.hpp"
#include <SDL.h>

namespace GameEngine
{
	void GameBase::Initialize()
	{
		m_Window = Window::Create(
			"Pack-Man Clone", 800, 600
		);
		GameWorld = std::make_unique<World>();
	}

	void GameBase::Run()
	{
		const Uint32 FramesPerSecond = 60;
		const Uint32 TicksPerFrame = 1000 / FramesPerSecond;
		Uint32 LastWorldTick = SDL_GetTicks();
		Uint32 FrameStart, FrameEnd, TicksThisFrame, DeltaTime;

		while (m_Window->IsOpened()) {

			m_Window->StartDrawing();

			//Here we handle world ticking, which also renders all actor SpriteComponents.
			FrameStart = SDL_GetTicks();
			DeltaTime = FrameStart - LastWorldTick;
			if (DeltaTime > 0)
			{
				GameWorld->Tick(DeltaTime);
				LastWorldTick = FrameStart;
			}

			m_Window->StopDrawing();

			FrameEnd = SDL_GetTicks();
			TicksThisFrame = FrameEnd - FrameStart;
			if (TicksThisFrame < TicksPerFrame)
				SDL_Delay(TicksPerFrame - TicksThisFrame);

		}
	}

	void GameBase::Exit()
	{
		Application::Quit();
	}
}
