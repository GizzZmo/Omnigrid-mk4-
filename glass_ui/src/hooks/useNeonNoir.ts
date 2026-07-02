import { useEffect, useState } from 'react';
import { useHalSocket } from './useHalSocket';

type UIState = 'STUDIO' | 'LIVE' | 'GHOST_PATCH' | 'EMERGENCY_PANIC';

interface NeonNoirTheme {
  primaryColor: string;
  glowIntensity: string;
  gridOpacity: number;
  fontFamily: string;
  vfxClass: string;
}

export const useNeonNoir = () => {
  const { telemetry, activeAgentOverride } = useHalSocket();
  const [uiState, setUiState] = useState<UIState>('STUDIO');
  const [theme, setTheme] = useState<NeonNoirTheme>({
    primaryColor: '#FFB000',
    glowIntensity: '0px 0px 10px rgba(255, 176, 0, 0.5)',
    gridOpacity: 1,
    fontFamily: "'Inter', sans-serif",
    vfxClass: 'vfx-clean',
  });

  useEffect(() => {
    if (telemetry.panicRelayEngaged) {
      setUiState('EMERGENCY_PANIC');
      setTheme({
        primaryColor: '#FFFFFF',
        glowIntensity: 'none',
        gridOpacity: 0.2,
        fontFamily: "'Courier New', monospace",
        vfxClass: 'vfx-hard-cut',
      });
      return;
    }

    if (activeAgentOverride) {
      setTheme((prev) => ({
        ...prev,
        primaryColor: activeAgentOverride.ui_override_color,
        glowIntensity: `0px 0px 20px ${activeAgentOverride.ui_override_color}`,
        vfxClass: activeAgentOverride.vfx_trigger || 'vfx-glitch',
      }));
      return;
    }

    if (telemetry.ghostPatchActive) {
      setUiState('GHOST_PATCH');
      setTheme({
        primaryColor: '#D500F9',
        glowIntensity: '0px 0px 15px rgba(213, 0, 249, 0.8)',
        gridOpacity: 0.5,
        fontFamily: "'Cinzel', serif",
        vfxClass: 'vfx-chromatic-aberration',
      });
    } else if (telemetry.liveModeActive) {
      setUiState('LIVE');
      setTheme({
        primaryColor: '#00E5FF',
        glowIntensity: '0px 0px 12px rgba(0, 229, 255, 0.6)',
        gridOpacity: 0.8,
        fontFamily: "'Inter', sans-serif",
        vfxClass: 'vfx-reactive',
      });
    } else {
      setUiState('STUDIO');
      setTheme({
        primaryColor: '#FFB000',
        glowIntensity: '0px 0px 5px rgba(255, 176, 0, 0.3)',
        gridOpacity: 1,
        fontFamily: "'Inter', sans-serif",
        vfxClass: 'vfx-clean',
      });
    }
  }, [telemetry, activeAgentOverride]);

  return { uiState, theme };
};
