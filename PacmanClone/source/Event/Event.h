#pragma once

#include "PacmanCore.h"

template <typename... Args>
class Event {
public:
    using Callback = std::function<void(Args...)>;
    using CallbackPtr = std::shared_ptr<Callback>;
    using Callbacks = std::vector<CallbackPtr>;

    // Register a callback function
    CallbackPtr AddListener(Callback callback) {
        CallbackPtr pointer = std::make_shared<Callback>(callback);
        listeners.push_back(pointer);
        return pointer;
    }

    // Unregister a callback function
    void RemoveListener(CallbackPtr callback) {
        listeners.erase(std::find(listeners.begin(), listeners.end(), callback));
    }

    // Invoke all registered callbacks
    void Invoke(Args... args) {
        for (auto & listener : listeners) {
            listener.get()->operator()(args ...);
        }
    }

private:
    Callbacks listeners;
};

