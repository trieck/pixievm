#pragma once

#include <atomic>
#include <memory>
#include <mutex>

template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        if (!initialized_.load()) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!initialized_.load()) {
                instance_ = std::unique_ptr<T>(new T());
                initialized_ = true;
            }
        }

        return *instance_;
    }

private:
    static std::mutex mutex_;
    static std::atomic_bool initialized_;
    static std::unique_ptr<T> instance_;
};


template <typename T>
std::atomic_bool Singleton<T>::initialized_ = { false };

template <typename T>
std::mutex Singleton<T>::mutex_;

template <typename T>
std::unique_ptr<T> Singleton<T>::instance_;
