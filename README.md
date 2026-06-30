# Omnigrid-mk4-
The system is divided into four isolated operational planes:  1. **The Audio Bus (Core DSP):** Bare-metal C++ executing SIMD instructions. Runs on a dedicated hardware interrupt with a strict 0.66ms processing budget (64 samples @ 96kHz). Zero mutexes. Zero system calls. 2. **The DMZ (HAL):** Lock-free ring buffers (`hal_dmz/lock_free_queue.h`) fac
