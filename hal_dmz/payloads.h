#pragma once

#include <cstdint>
#include <string_view>

struct ParameterUpdate {
    std::string_view node_id;
    std::string_view param_id;
    float value;
};

struct TelemetryData {
    std::uint64_t timestamp = 0;
    float rms_level = 0.0f;
    float dsp_load_percent = 0.0f;
    float core_temp = 0.0f;
    float peak_lufs = -60.0f;
};
