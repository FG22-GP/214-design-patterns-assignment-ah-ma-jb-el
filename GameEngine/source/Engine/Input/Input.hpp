#pragma once

#include "Core.hpp"
#include <SDL_events.h>

enum KeyDownEvent
{
    KEY_DOWN_INPUT_W,
    KEY_DOWN_INPUT_A,
    KEY_DOWN_INPUT_S,
    KEY_DOWN_INPUT_D,
    KEY_DOWN_INPUT_ARROW_UP,
    KEY_DOWN_INPUT_ARROW_LEFT,
    KEY_DOWN_INPUT_ARROW_DOWN,
    KEY_DOWN_INPUT_ARROW_RIGHT,
    KEY_DOWN_INPUT_SPACE,
    KEY_DOWN_INPUT_ENTER,
    KEY_DOWN_INPUT_LSHIFT,
    KEY_DOWN_INPUT_LCTRL,
    KEY_DOWN_INPUT_LALT,
    KEY_DOWN_INPUT_RSHIFT,
    KEY_DOWN_INPUT_RCTRL,
    KEY_DOWN_INPUT_RALT,
    KEY_DOWN_INPUT_ESCAPE,
    KEY_DOWN_INPUT_F1,
    KEY_DOWN_INPUT_F2,
    KEY_DOWN_INPUT_F3,
    KEY_DOWN_INPUT_F4,
    KEY_DOWN_INPUT_F5,
    KEY_DOWN_INPUT_F6,
    KEY_DOWN_INPUT_F7,
    KEY_DOWN_INPUT_F8,
    KEY_DOWN_INPUT_F9,
    KEY_DOWN_INPUT_F10,
    KEY_DOWN_INPUT_F11,
    KEY_DOWN_INPUT_F12
};

// Map to link SDL key codes to custom enum values
inline std::unordered_map<SDL_Keycode, KeyDownEvent> SDLKeyToKeyDownEvent = {
    { SDLK_w, KEY_DOWN_INPUT_W },
    { SDLK_a, KEY_DOWN_INPUT_A },
    { SDLK_s, KEY_DOWN_INPUT_S },
    { SDLK_d, KEY_DOWN_INPUT_D },
    { SDLK_UP, KEY_DOWN_INPUT_ARROW_UP },
    { SDLK_LEFT, KEY_DOWN_INPUT_ARROW_LEFT },
    { SDLK_DOWN, KEY_DOWN_INPUT_ARROW_DOWN },
    { SDLK_RIGHT, KEY_DOWN_INPUT_ARROW_RIGHT },
    { SDLK_SPACE, KEY_DOWN_INPUT_SPACE },
    { SDLK_RETURN, KEY_DOWN_INPUT_ENTER },
    { SDLK_LSHIFT, KEY_DOWN_INPUT_LSHIFT },
    { SDLK_LCTRL, KEY_DOWN_INPUT_LCTRL },
    { SDLK_LALT, KEY_DOWN_INPUT_LALT },
    { SDLK_RSHIFT, KEY_DOWN_INPUT_RSHIFT },
    { SDLK_RCTRL, KEY_DOWN_INPUT_RCTRL },
    { SDLK_RALT, KEY_DOWN_INPUT_RALT },
    { SDLK_ESCAPE, KEY_DOWN_INPUT_ESCAPE },
    { SDLK_F1, KEY_DOWN_INPUT_F1 },
    { SDLK_F2, KEY_DOWN_INPUT_F2 },
    { SDLK_F3, KEY_DOWN_INPUT_F3 },
    { SDLK_F4, KEY_DOWN_INPUT_F4 },
    { SDLK_F5, KEY_DOWN_INPUT_F5 },
    { SDLK_F6, KEY_DOWN_INPUT_F6 },
    { SDLK_F7, KEY_DOWN_INPUT_F7 },
    { SDLK_F8, KEY_DOWN_INPUT_F8 },
    { SDLK_F9, KEY_DOWN_INPUT_F9 },
    { SDLK_F10, KEY_DOWN_INPUT_F10 },
    { SDLK_F11, KEY_DOWN_INPUT_F11 },
    { SDLK_F12, KEY_DOWN_INPUT_F12 }
};

namespace GameEngine
{
    class Input
    {
    public:
        GAME_API static void HandleInput();
        GAME_API static void RegisterInputEvent(const KeyDownEvent keyDownEvent, const std::function<void()>& callback);
        GAME_API static void UnRegisterInputEvent(const KeyDownEvent keyDownEvent, const std::function<void()>& callback);

        static SDL_Keycode GetSDLKeyCodeFromEvent(const KeyDownEvent& event)
        {
            for (const auto& pair : SDLKeyToKeyDownEvent) {
                if (pair.second == event) {
                    return pair.first;
                }
            }
            return SDLK_UNKNOWN; // Return unknown if not found
        }
        
    private:
        static std::unordered_map<SDL_Keycode, std::vector<std::function<void()>>> EventCallbacks;    

    };
}
