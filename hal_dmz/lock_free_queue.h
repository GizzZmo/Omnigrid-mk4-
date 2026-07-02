#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class ControlQueue {
public:
    bool pop(T& value) {
        if (read_idx_ == write_idx_) {
            return false;
        }
        value = buffer_[read_idx_ % Capacity];
        ++read_idx_;
        return true;
    }

    bool push(const T& value) {
        if ((write_idx_ - read_idx_) >= Capacity) {
            return false;
        }
        buffer_[write_idx_ % Capacity] = value;
        ++write_idx_;
        return true;
    }

private:
    std::array<T, Capacity> buffer_{};
    std::size_t read_idx_ = 0;
    std::size_t write_idx_ = 0;
};

template <typename T, std::size_t Capacity>
using TelemetryQueue = ControlQueue<T, Capacity>;
