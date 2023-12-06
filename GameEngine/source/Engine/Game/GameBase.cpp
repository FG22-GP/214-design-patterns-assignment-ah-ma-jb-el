#include "Core.hpp"
#include "GameBase.h"
#include "Engine/Application/Application.hpp"
#include "Engine/Window/Window.hpp"

namespace GameEngine
{
	void GameBase::Initialize()
	{
		m_Window = Window::Create(
			"Pack-Man Clone", 800, 600
		);
	}

	void GameBase::Run()
	{
		while (m_Window->IsOpened()) {
			// Update Input
			// Update Actors

			m_Window->StartDrawing();

			// Render Actors

			m_Window->StopDrawing();
		}
	}

	void GameBase::Exit()
	{
		Application::Quit();
	}
}
