#include "Core.hpp"
#include "Input.hpp"

#include <SDL.h>
#include <SDL_events.h>

namespace GameEngine
{
    std::unordered_map<SDL_EventType, std::vector<std::function<void(SDL_Event)>>> Input::EventCallbacks;

    void Input::HandleInput()
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            auto eventType = static_cast<SDL_EventType>(Event.type);
            auto it = EventCallbacks.find(eventType);
            if (it != EventCallbacks.end()) {
                for (auto& callback : it->second) {
                    callback(Event);
                }
            }
        }
    }

    void Input::SubscribeInputEvent(const SDL_EventType eventType, const std::function<void(SDL_Event)>& callback)
    {
        EventCallbacks[eventType].push_back(callback);
    }

    void Input::UnsubscribeInputEvent(SDL_EventType eventType, std::function<void(SDL_Event)> callback)
    {
        const auto it = EventCallbacks.find(eventType);
        if (it != EventCallbacks.end()) {
            auto& callbacks = it->second;
            callbacks.erase(it->second.begin(), it->second.end());
        }
    }

}
