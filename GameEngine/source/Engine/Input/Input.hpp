#pragma once

#include "Core.hpp"

//#include <SDL.h>
#include <SDL_events.h>

namespace GameEngine
{
    class Input
    {
    public:
        GAME_API static void HandleInput();
        GAME_API static void SubscribeInputEvent(const SDL_EventType eventType, const std::function<void(SDL_Event)>& callback);
        GAME_API static void UnsubscribeInputEvent(const SDL_EventType eventType, const std::function<void(SDL_Event)>& callback);

    private:
        static std::unordered_map<SDL_EventType, std::vector<std::function<void(SDL_Event)>>> EventCallbacks;    
    };
}
