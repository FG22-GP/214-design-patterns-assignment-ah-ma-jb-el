#pragma once

#include "PacmanCore.h"

template <typename... Args>
class Event {
public:
    using Callback = std::function<void(Args...)>;

    // Register a callback function
    void AddListener(Callback callback) {
        listeners.push_back(callback);
    }

    // Unregister a callback function
    void RemoveListener(Callback callback) {
        auto it = std::find(listeners.begin(), listeners.end(), callback);
        if (it != listeners.end()) {
            listeners.erase(it);
        }
    }

    // Invoke all registered callbacks
    void Invoke(Args... args) {
        for (const auto& listener : listeners) {
            listener(args...);
        }
    }

private:
    std::vector<Callback> listeners;
};

