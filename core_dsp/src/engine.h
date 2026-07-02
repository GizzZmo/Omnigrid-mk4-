#pragma once

#include <cstddef>
#include <cstdint>

#include "hal_dmz/payloads.h"

enum TelemetryEvent {
    CRITICAL_PANIC_ENGAGED,
};

class Graph {
public:
    void set_parameter(std::string_view, std::string_view, float) {}
    void process_block(float*, float*, std::size_t) {}
};

class HardwareTimer {
public:
    static std::uint64_t get_ticks() { return 0; }
};

class HardwareSensors {
public:
    static float read_temp() { return 42.0f; }
};

class AudioEngine {
public:
    void process_hardware_interrupt(float* in_buffer, float* out_buffer, std::size_t num_samples);

private:
    Graph active_graph;

    void execute_hard_bypass(float*, float*, std::size_t) {}
    void log_telemetry_event(TelemetryEvent) {}
    float calculate_rms(float*, std::size_t) { return 0.0f; }
    float calculate_execution_time() { return 0.1f; }
};
