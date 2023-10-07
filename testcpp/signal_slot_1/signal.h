#pragma once
#include "slot.h"
template <typename... Args>
class signal
{
public:
    signal(const signal &) = delete;
    signal(signal &&) = delete;
    signal &operator=(const signal &) = delete;

    signal() = default;
    ~signal() = default;

    void connect(slot<Args...> &slot)
    {
        _connectedSlots.push_back(&slot);
    }

    void disconnect(slot<Args...> &slot)
    {
        // using iterator for safe deletion
        for (auto it = _connectedSlots.begin(); it != _connectedSlots.end();)
        {
            if (*it == slot)
                it = _connectedSlots.erase();
            else
                ++it;
        }
    }
    void disconnect()
    {
        _connectedSlots.clear();
    }

    void emit(Args... parameters)
    {
        for (auto &el : _connectedSlots)
            (*el)(parameters...); // using () operator overloading
    }

private:
    std::vector<slot<Args...> *> _connectedSlots;
};