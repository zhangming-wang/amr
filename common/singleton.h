#pragma once

template <typename T>
class Singleton {
protected:
    Singleton() = default; // 防止外部实例化
    ~Singleton() = default;

public:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    static T &instance() {
        static T inst;
        return inst;
    }
};