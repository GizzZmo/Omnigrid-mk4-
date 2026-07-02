import json
import time

from hal_bridge import ControlQueue, TelemetryStream

THERMAL_THRESHOLD_C = 90.0
CRITICAL_LUFS = -0.1


class WardenAgent:
    def __init__(self):
        self.telemetry = TelemetryStream()
        self.control_bus = ControlQueue()
        self.signature = "WARD-0x0042"
        self.is_gated = False

    def check_ai_gating_status(self):
        self.is_gated = self.telemetry.read_gating_pin()

    def evaluate_system_state(self, telemetry_frame):
        if self.is_gated:
            return

        if telemetry_frame.core_temp >= THERMAL_THRESHOLD_C:
            self._trigger_intervention(
                target="DSP_Core0",
                action="Thermal threshold breached. Recommend Panic Relay.",
                ui_color_shift="#D50000",
            )

        if telemetry_frame.peak_lufs >= CRITICAL_LUFS:
            self.control_bus.push_update(
                {
                    "node_id": "MASTER_BUS",
                    "param_id": "GAIN",
                    "value": -3.0,
                    "signature": self.signature,
                }
            )
            self._trigger_intervention(
                target="Master_Bus",
                action="Hard clipping detected. Clamping gain by -3.0dB.",
                ui_color_shift="#D50000",
            )

    def _trigger_intervention(self, target, action, ui_color_shift):
        alert_payload = {
            "agent": "Warden",
            "type": "ALERT",
            "target": target,
            "action": action,
            "ui_override_color": ui_color_shift,
        }
        print(f"[{self.signature}] DISPATCHING: {json.dumps(alert_payload)}")

    def run(self):
        print(f"[{self.signature}] The Warden is online. Monitoring DSP telemetry.")
        while True:
            self.check_ai_gating_status()
            current_frame = self.telemetry.pull_latest()
            if current_frame:
                self.evaluate_system_state(current_frame)
            time.sleep(0.016)


if __name__ == "__main__":
    warden = WardenAgent()
    warden.run()
