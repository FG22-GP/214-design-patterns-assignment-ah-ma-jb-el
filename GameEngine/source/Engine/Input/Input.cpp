#include "Core.hpp"
#include "Input.hpp"

#include <SDL.h>
#include <SDL_events.h>

namespace GameEngine
{
    
    std::unordered_map<SDL_Keycode, std::vector<std::function<void()>>> Input::EventCallbacks;

    void Input::HandleInput()
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event) != 0) {
            if (Event.type == SDL_KEYDOWN) { // If the event is a key press
                const SDL_Keycode keyCode = Event.key.keysym.sym; // Get SDL key code from the event
                // Find corresponding KeyDownEvent in the mapping
                SDLKeyToKeyDownEvent.find(keyCode);
                auto eventType = static_cast<SDL_EventType>(Event.type);
                auto it = EventCallbacks.find(eventType);
                if (it != EventCallbacks.end()) {
                    // Execute callbacks subscribed to this event type
                    for (auto& callback : it->second) {
                        callback();
                    }
                }
            }
        }
    }

    void Input::SubscribeInputEvent(const KeyDownEvent keyDownEvent, const std::function<void()>& callback)
    {
        // Get SDL key code from the event
        const SDL_Keycode keyCode = GetSDLKeyCodeFromEvent(keyDownEvent);
        // Subscribe a callback function to a specific event type
        EventCallbacks[keyCode].push_back(callback);
    }

    void Input::UnsubscribeInputEvent(const KeyDownEvent keyDownEvent, const std::function<void()>& callback)
    {
        // Get SDL key code from the event
        const SDL_Keycode keyCode = GetSDLKeyCodeFromEvent(keyDownEvent);
        // Unsubscribe a callback function from a specific event type
        const auto it = EventCallbacks.find(keyCode);
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
