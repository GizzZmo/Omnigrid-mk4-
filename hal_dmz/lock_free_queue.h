#pragma once

#include <atomic>
#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class ControlQueue {
public:
    bool pop(T& value) {
        const auto read_idx = read_idx_.load(std::memory_order_relaxed);
        const auto write_idx = write_idx_.load(std::memory_order_acquire);
        if (read_idx == write_idx) {
            return false;
        }
        value = buffer_[read_idx % Capacity];
        read_idx_.store(read_idx + 1, std::memory_order_release);
        return true;
    }

    bool push(const T& value) {
        const auto write_idx = write_idx_.load(std::memory_order_relaxed);
        const auto read_idx = read_idx_.load(std::memory_order_acquire);
        if ((write_idx - read_idx) >= Capacity) {
            return false;
        }
        buffer_[write_idx % Capacity] = value;
        write_idx_.store(write_idx + 1, std::memory_order_release);
        return true;
    }

private:
    std::array<T, Capacity> buffer_{};
    std::atomic<std::size_t> read_idx_{0};
    std::atomic<std::size_t> write_idx_{0};
};

template <typename T, std::size_t Capacity>
using TelemetryQueue = ControlQueue<T, Capacity>;
