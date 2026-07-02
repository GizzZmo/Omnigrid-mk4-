#include "hal_dmz/lock_free_queue.h"
#include "hal_dmz/payloads.h"

ControlQueue<ParameterUpdate, 1024> dmz_rx_queue;
TelemetryQueue<TelemetryData, 1024> dmz_tx_queue;
