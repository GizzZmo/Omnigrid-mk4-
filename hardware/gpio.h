#pragma once

constexpr int PIN_PANIC_RELAY = 1;
constexpr int HIGH = 1;

inline int GPIO_ReadPin(int) {
    return 0;
}
