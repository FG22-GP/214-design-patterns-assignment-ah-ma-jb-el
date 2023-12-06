#include "Core.hpp"
#include "Window.hpp"

#include "Engine/Renderer/Interfaces/IRenderable.h"
#include "Data/Vectors/Point2.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "SDL.h"

namespace GameEngine
{
	std::shared_ptr<Window> Window::s_Main;

// CONSTRUCTORS

	Window::Window(const std::string& title, const uint32_t width, const uint32_t height){
		auto* window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_SHOWN
		);
		m_Window.reset(window);
		m_IsOpened = true;

		m_renderer = std::make_shared<Renderer>(
			Renderer(*this)
		);
	}

// STATES

	bool Window::IsOpened(){
		return m_IsOpened;
	}

// GETTERS

	std::shared_ptr<Window> Window::GetMain(){
		return s_Main;
	}

	std::shared_ptr<Renderer> Window::GetRenderer() const {
		return m_renderer;
	}

	Point2 Window::GetSize() const {
		Point2 point;

		SDL_GetWindowSize(
			m_Window.get(),
			&point.x,
			&point.y
		);
		return point;
	}

// WINDOW

	std::shared_ptr<Window> Window::Create(const std::string& title, const uint32_t width, const uint32_t height){
		auto* window = new Window(
			title, width, height
		);
		s_Main.reset(window);
		return s_Main;
	}

	void Window::StartDrawing(){
		m_renderer->StartDrawing();
	}

	void Window::Draw(IRenderable& render){
		m_renderer->Draw(render);
	}

	void Window::StopDrawing(){
		m_renderer->StopDrawing();
	}

	void Window::Close(){
		m_IsOpened = false;
	}

// OPERATORS

	Window::operator SDL_Window* (){ return m_Window.get(); }

	void Window::Deleter::operator()(SDL_Window* w) const noexcept { 
		SDL_DestroyWindow(w);
	}

}