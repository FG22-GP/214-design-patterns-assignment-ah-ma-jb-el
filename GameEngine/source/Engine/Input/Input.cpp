#include "Core.hpp"
#include "Input.hpp"

#include <SDL.h>
#include <SDL_events.h>

namespace GameEngine
{
    //  TODO: Maybe remove use of SDL_EventType and use a custom enum class instead
    
    std::unordered_map<SDL_EventType, std::vector<std::function<void(SDL_Event)>>> Input::EventCallbacks;

    void Input::HandleInput()
    {
        // Retrieve events and handle subscriptions
        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {
            auto eventType = static_cast<SDL_EventType>(Event.type); // Convert SDL event type
            auto it = EventCallbacks.find(eventType); // Find event type in subscriptions
            if (it != EventCallbacks.end()) {
                // Execute callbacks subscribed to this event type
                for (auto& callback : it->second) {
                    callback(Event);
                }
            }
        }
    }

    void Input::SubscribeInputEvent(const SDL_EventType eventType, const std::function<void(SDL_Event)>& callback)
    {
        // Subscribe a callback function to a specific event type
        EventCallbacks[eventType].push_back(callback);
    }

    void Input::UnsubscribeInputEvent(const SDL_EventType eventType, const std::function<void(SDL_Event)>& callback)
    {
        // Unsubscribe a callback function from a specific event type
        const auto it = EventCallbacks.find(eventType);
        if (it != EventCallbacks.end()) {
            auto& callbacks = it->second;
            // Search for the callback in the subscribed list and remove it if found
            const auto foundCallback = std::ranges::find_if(callbacks, [&](const auto& func) {
                return &func == &callback; // Compare addresses to identify the function
            });
            if (foundCallback != callbacks.end()) {
                callbacks.erase(foundCallback); // Remove the found callback
            }
        }
    }


}
