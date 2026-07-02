#include "engine.h"

#include "hal_dmz/lock_free_queue.h"
#include "hardware/gpio.h"

extern ControlQueue<ParameterUpdate, 1024> dmz_rx_queue;
extern TelemetryQueue<TelemetryData, 1024> dmz_tx_queue;

void AudioEngine::process_hardware_interrupt(float* in_buffer, float* out_buffer, std::size_t num_samples) {
    if (GPIO_ReadPin(PIN_PANIC_RELAY) == HIGH) {
        execute_hard_bypass(in_buffer, out_buffer, num_samples);
        log_telemetry_event(CRITICAL_PANIC_ENGAGED);
        return;
    }

    ParameterUpdate update;
    while (dmz_rx_queue.pop(update)) {
        active_graph.set_parameter(update.node_id, update.param_id, update.value);
    }

    active_graph.process_block(in_buffer, out_buffer, num_samples);

    TelemetryData t_data;
    t_data.timestamp = HardwareTimer::get_ticks();
    t_data.rms_level = calculate_rms(out_buffer, num_samples);
    t_data.dsp_load_percent = calculate_execution_time() / 0.66f * 100.0f;
    t_data.core_temp = HardwareSensors::read_temp();

    dmz_tx_queue.push(t_data);
}
