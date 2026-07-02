export interface Telemetry {
  panicRelayEngaged: boolean;
  ghostPatchActive: boolean;
  liveModeActive: boolean;
}

export interface AgentOverride {
  ui_override_color: string;
  vfx_trigger?: string;
}

export const useHalSocket = () => {
  return {
    telemetry: {
      panicRelayEngaged: false,
      ghostPatchActive: false,
      liveModeActive: false,
    } as Telemetry,
    activeAgentOverride: null as AgentOverride | null,
  };
};
