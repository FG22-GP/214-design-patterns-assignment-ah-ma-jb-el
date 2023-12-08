#include "Core.hpp"
#include "GameBase.h"

#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "Engine/Asset/AssetLoader.hpp"
#include "Engine/Application/Application.hpp"
#include "Engine/Window/Window.hpp"
#include "Engine/Input/Input.hpp"
#include <SDL.h>

namespace GameEngine
{
	void GameBase::Initialize()
	{
		Application::Init();

		m_Window = Window::Create(
			"Pack-Man Clone", 800, 600
		);
	}

	void GameBase::Run()
	{
		const Uint32 FramesPerSecond = 60;
		const Uint32 TicksPerFrame = 1000 / FramesPerSecond;
		Uint32 LastWorldTick = SDL_GetTicks();
		Uint32 FrameStart, FrameEnd, TicksThisFrame, DeltaTime;

		while (m_Window->IsOpened()) {

			FrameStart = SDL_GetTicks();

			Input::HandleInput();

			//Here we handle world ticking, which also renders all actor SpriteComponents.
			DeltaTime = FrameStart - LastWorldTick;
			if (DeltaTime > 0)
			{
				HandleTick(static_cast<float>(DeltaTime * 0.001));
				LastWorldTick = FrameStart;
			}

			m_Window->StartDrawing();
			HandleRendering();
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
