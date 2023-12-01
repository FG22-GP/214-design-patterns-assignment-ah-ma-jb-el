#include "Core.hpp"
#include "Window.hpp"

#include "SDL.h"

namespace GameEngine
{
// SINGLETON

	Window& Window::GetInstance(){
		static Window instance;
		return instance;
	}

// CONSTRUCTORS

	Window::Window() :
		m_IsOpened(false),
		m_Window(nullptr){}

// STATES

	bool Window::IsOpened(){
		auto& instance = GetInstance();
		return instance.m_IsOpened;
	}

// WINDOW

	void Window::Create(const std::string& title, const uint32_t width, const uint32_t height){
		auto& instance = GetInstance();
		if (instance.m_IsOpened) return;

		auto* window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			width, height, 
			SDL_WINDOW_SHOWN
		);
		instance.m_Window.release();
		instance.m_Window.reset(window);

		instance.m_IsOpened = true;
	}

	void Window::Close(){
		auto& instance = GetInstance();
		instance.m_IsOpened = false;
	}

	void Window::Clean(){
		auto& instance = GetInstance();
		
		SDL_DestroyWindow(
			instance.m_Window.get()
		);
		instance.m_Window = nullptr;
	}

// OPERATORS

	void Window::Deleter::operator()(SDL_Window* w) const noexcept { delete(w); }

}