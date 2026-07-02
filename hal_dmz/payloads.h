#pragma once

#include <cstdint>

struct ParameterUpdate {
    const char* node_id;
    const char* param_id;
    float value;
};

struct TelemetryData {
    std::uint64_t timestamp = 0;
    float rms_level = 0.0f;
    float dsp_load_percent = 0.0f;
    float core_temp = 0.0f;
    float peak_lufs = -60.0f;
};
