import random
from dataclasses import dataclass, field


@dataclass
class TelemetryFrame:
    fft_bins: list[float] = field(default_factory=lambda: [0.0] * 64)
    core_temp: float = 40.0
    peak_lufs: float = -12.0


class TelemetryStream:
    def read_ghost_patch_pin(self) -> bool:
        return False

    def read_gating_pin(self) -> bool:
        return False

    def pull_latest(self):
        if random.random() < 0.1:
            return None
        return TelemetryFrame()


class ControlQueue:
    def push_update(self, payload: dict) -> None:
        # Scaffold bridge: this local stub accepts updates but does not forward them yet.
        _ = payload
