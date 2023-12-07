#pragma once

#include "Core.hpp"
#include "KeyboardKey.h"

enum KeyEvent
{
    KEY_DOWN_EVENT,
    KEY_UP_EVENT,
};

namespace GameEngine
{
    class Input
    {
    public:
        GAME_API static void HandleInput();
        GAME_API static void RegisterInputEvent(const KeyEvent keyEvent, const KeyboardKey key, const std::function<void()>& callback);
        GAME_API static void UnRegisterInputEvent(const KeyEvent keyEvent, const KeyboardKey key, const std::function<void()>& callback);
        
    private:
        static std::unordered_map<KeyboardKey, std::vector<std::function<void()>>> KeyDownCallbacks;
        static std::unordered_map<KeyboardKey, std::vector<std::function<void()>>> KeyUpCallbacks;

    };
}
