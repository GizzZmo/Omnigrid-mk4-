# Omni-Grid Mk-IV

![CI](https://github.com/GizzZmo/Omnigrid-mk4-/actions/workflows/ci.yml/badge.svg)
![Generate Screenshots](https://github.com/GizzZmo/Omnigrid-mk4-/actions/workflows/screenshots.yml/badge.svg)

Omni-Grid Mk-IV is a cross-layer prototype that combines:
- a C++ DSP core,
- lock-free DMZ queue primitives,
- Python-based AI oversight agents,
- and a React/TypeScript UI hook layer.

---

## About

This repository captures the foundation of an audio-routing architecture where real-time processing and higher-level control are intentionally separated:

- **The Metal (`core_dsp/`)** handles deterministic audio-path logic.
- **The DMZ (`hal_dmz/`)** provides lock-free payload transport types and queues.
- **The Agent Layer (`ai_agents/`)** models supervisory behavior through Python daemons.
- **The Glass (`glass_ui/`)** adapts UI state from telemetry and agent overrides.

Current status: this repo is a scaffold/prototype with working structure and stubs, suitable for extension into production-grade DSP + control software.

---

## Repository Layout

```text
Omnigrid-mk4-/
├── .github/workflows/         # CI and screenshot artifact workflows
├── core_dsp/                  # C++20 DSP library build target
│   ├── src/
│   │   ├── engine.cpp
│   │   ├── engine.h
│   │   └── queues.cpp
│   └── CMakeLists.txt
├── hal_dmz/
│   ├── lock_free_queue.h
│   └── payloads.h
├── hardware/
│   └── gpio.h
├── ai_agents/
│   ├── src/
│   │   ├── ghost_coder.py
│   │   ├── hal_bridge.py
│   │   ├── llm_bridge.py
│   │   └── warden.py
│   └── requirements.txt
├── glass_ui/
│   ├── src/hooks/
│   │   ├── useHalSocket.ts
│   │   └── useNeonNoir.ts
│   └── package.json
└── README.md
```

---

## Architecture Overview

### 1) Core DSP (`core_dsp`)
- Builds a static library via CMake.
- Processes control updates from DMZ queues before block processing.
- Exports telemetry values such as RMS, DSP load, and core temperature.
- Includes panic-relay short-circuit behavior via `hardware/gpio.h`.

### 2) DMZ Primitives (`hal_dmz`)
- `lock_free_queue.h`: generic lock-free ring-buffer queue template.
- `payloads.h`: shared payload contracts (`ParameterUpdate`, `TelemetryData`).
- Keeps control/telemetry exchange decoupled from audio processing code.

### 3) AI Agents (`ai_agents`)
- `warden.py`: monitors thermal/load conditions and emits interventions.
- `ghost_coder.py`: simulates emergent routing updates and UI override events.
- `llm_bridge.py`: lightweight bridge entrypoint placeholder.
- `hal_bridge.py`: local telemetry/control stub used by agent scripts.

### 4) UI Hooks (`glass_ui`)
- `useHalSocket.ts` provides typed telemetry + agent override state.
- `useNeonNoir.ts` maps system state into dynamic UI themes.
- `npm run dev` currently runs a scaffold script for validation.

---

## Getting Started

### Prerequisites
- CMake 3.16+
- C++ compiler with C++20 support
- Python 3.10+
- Node.js 18+

### Build DSP Library
```bash
cd core_dsp
cmake -S . -B build
cmake --build build
```

### Validate Python Agent Sources
```bash
cd ai_agents
python -m py_compile src/*.py
```

### Run UI Scaffold Script
```bash
cd glass_ui
npm install
npm run dev
```

---

## Wiki

Project wiki (for architecture notes, runbooks, and expansion docs):

- **Wiki Home:** https://github.com/GizzZmo/Omnigrid-mk4-/wiki

Suggested wiki pages to maintain:
- System architecture deep dive
- DSP timing budget and real-time constraints
- DMZ payload contract/versioning
- Agent behavior policies
- UI state model and theming rules
- Hardware integration notes

---

## CI Workflows

- **CI (`ci.yml`)** configures/builds DSP, checks Python source syntax, and validates UI startup script.
- **Generate Screenshots (`screenshots.yml`)** builds a static artifact page and captures screenshot artifacts.

---

## Improvement Opportunities

- Add unit and integration tests for DSP queue/engine behavior.
- Replace Python bridge stubs with concrete transport implementations.
- Expand UI beyond hooks into a runnable component surface.
- Add explicit versioning and changelog/release process.
- Add a repository license file if/when licensing terms are finalized.

---

## Contributing

1. Fork and clone.
2. Create a feature branch.
3. Keep changes scoped and documented.
4. Ensure CI passes.
5. Open a pull request with a clear summary.

---

## License

No license file is currently present in this repository.  
Add a `LICENSE` file to define reuse and distribution terms.
