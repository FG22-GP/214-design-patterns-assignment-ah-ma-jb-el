#include "Core.hpp"
#include "Input.hpp"

#include <SDL_events.h>

namespace GameEngine
{
    
    std::unordered_map<KeyboardKey, std::vector<std::function<void()>>> Input::KeyDownCallbacks;
    std::unordered_map<KeyboardKey, std::vector<std::function<void()>>> Input::KeyUpCallbacks;

    void Input::HandleInput()
    {
        SDL_Event Event;
        std::unordered_map<KeyboardKey, std::vector<std::function<void()>>>* EventCallbacks;

        while (SDL_PollEvent(&Event) != 0) {

            if (Event.type == SDL_KEYDOWN)
                EventCallbacks = &KeyDownCallbacks;
            else if (Event.type == SDL_KEYUP)
                EventCallbacks = &KeyUpCallbacks;
            else
                continue;
            
            const SDL_Keycode keyCode = Event.key.keysym.sym; // Get SDL key code from the event
            const auto key = static_cast<KeyboardKey>(keyCode); // Cast SDL key code to KeyboardKey enum
            
            // Find corresponding KeyDownEvent in the mapping
            auto it = EventCallbacks->find(key);
            if (it != EventCallbacks->end()) {
                // Execute callbacks subscribed to this event type
                for (auto& callback : it->second) {
                    callback();
                }
            }
            
        }
    }

    // A bit hacky, but it works for now
    void Input::RegisterInputEvent(const KeyEvent keyEvent, const KeyboardKey key, const std::function<void()>& callback)
    {
        std::unordered_map<KeyboardKey, std::vector<std::function<void()>>>& EventCallbacks =
            (keyEvent == KEY_DOWN_EVENT) ? KeyDownCallbacks : KeyUpCallbacks;
        
        // Subscribe a callback function to a specific event type
        EventCallbacks[key].push_back(callback);
        
    }

    void Input::UnRegisterInputEvent(const KeyEvent keyEvent, const KeyboardKey key, const std::function<void()>& callback)
    {
        std::unordered_map<KeyboardKey, std::vector<std::function<void()>>>& EventCallbacks =
            (keyEvent == KEY_DOWN_EVENT) ? KeyDownCallbacks : KeyUpCallbacks;
        
        // Unsubscribe a callback function from a specific event type
        const auto it = EventCallbacks.find(key);
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
