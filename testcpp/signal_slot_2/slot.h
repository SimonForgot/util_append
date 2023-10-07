#pragma once
#include <functional>

template <typename... Args>
class slot
{
public:
    slot(const slot &) = delete;
    slot(slot &&) = delete;
    slot &operator=(const slot &) = delete;

    slot() : _init(false){};
    slot(std::function<void(Args...)> callback) : _init(true), _callback(callback) {}
    ~slot() = default;

    void operator()(Args... parameters)
    {
        // just implement it in call function
        this->call(parameters...);
    }
    void call(Args... parameters)
    {
        if (_init)
            _callback(parameters...);
    }

    void setSlotFunction(std::function<void(Args...)> callback)
    {
        _init = true;
        _callback = callback;
    }

private:
    bool _init;
    std::function<void(Args...)> _callback;
};