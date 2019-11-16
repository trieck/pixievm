#pragma once

template <typename T>
class PxSignal
{
public:
    PxSignal() = default;

    const T& connect(T&& t);

    template <typename... Args>
    void emit(Args&&... args);

private:
    std::vector<T> slots_;
};

template <typename T>
const T& PxSignal<T>::connect(T&& t)
{
    return *slots_.emplace(slots_.end(), std::move(t));
}

template <typename T>
template <typename ... Args>
void PxSignal<T>::emit(Args&&... args)
{
    for (auto& slot : slots_) {
        slot(std::forward<Args>(args)...);
    }
}
