#ifndef TIMED_SHARED_PTR_HPP
#define TIMED_SHARED_PTR_HPP

#include <chrono>
#include <atomic>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
using clockTime = std::chrono::time_point<Clock>;
using milliSeconds = std::chrono::milliseconds;

template<typename T>
class TimedSharedPtr {
private:
    struct ControlBlock {
        T* ptr;
        std::atomic<long> count;
        clockTime start;
        milliSeconds duration;

        ControlBlock(T* p, long ms)
            : ptr(p), count(1), start(Clock::now()), duration(ms) {
            std::cout << "ControlTimedSharedPtr "
                      << static_cast<void*>(ptr)
                      << " start: 0 ms\n";
        }

        ~ControlBlock() {
            auto elapsed = std::chrono::duration_cast<milliSeconds>(
                Clock::now() - start
            ).count();
            std::cout << "ControlTimedSharedPtr "
                      << static_cast<void*>(ptr)
                      << " end: " << elapsed << " ms\n";
        }
    };

    ControlBlock* ctrl = nullptr;

    void release() {
        if (ctrl && --ctrl->count == 0) {
            delete ctrl->ptr;
            delete ctrl;
        }
    }

public:
    TimedSharedPtr() = default;
    TimedSharedPtr(T* raw, long ms) : ctrl(new ControlBlock(raw, ms)) {}
    explicit TimedSharedPtr(T* raw) : ctrl(new ControlBlock(raw, 1000)) {}

    TimedSharedPtr(const TimedSharedPtr& o) noexcept : ctrl(o.ctrl) {
        if (ctrl) ctrl->count++;
    }
    TimedSharedPtr(TimedSharedPtr&& o) noexcept : ctrl(o.ctrl) {
        o.ctrl = nullptr;
    }
    TimedSharedPtr& operator=(const TimedSharedPtr& o) noexcept {
        if (this != &o) {
            release();
            ctrl = o.ctrl;
            if (ctrl) ctrl->count++;
        }
        return *this;
    }
    TimedSharedPtr& operator=(TimedSharedPtr&& o) noexcept {
        if (this != &o) {
            release();
            ctrl = o.ctrl;
            o.ctrl = nullptr;
        }
        return *this;
    }
    ~TimedSharedPtr() { release(); }

    long use_count() const noexcept {
        return ctrl ? ctrl->count.load() : 0;
    }

    T* get() const noexcept {
        if (!ctrl || !ctrl->ptr) return nullptr;
        auto elapsed = std::chrono::duration_cast<milliSeconds>(
            Clock::now() - ctrl->start
        );
        if (elapsed > ctrl->duration) {
            std::cout << "Yeo! Expired ";
            return nullptr;
        }
        return ctrl->ptr;
    }

    T& operator*()  const { return *get(); }
    T* operator->() const { return get(); }

    void reset() noexcept {
        release();
        ctrl = nullptr;
    }
};

#endif
