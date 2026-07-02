#pragma once

#include <array>
#include <cstdint>

struct ParameterUpdate {
    std::array<char, 32> node_id{};
    std::array<char, 32> param_id{};
    float value = 0.0f;
};

struct TelemetryData {
    std::uint64_t timestamp = 0;
    float rms_level = 0.0f;
    float dsp_load_percent = 0.0f;
    float core_temp = 0.0f;
    float peak_lufs = -60.0f;
};
