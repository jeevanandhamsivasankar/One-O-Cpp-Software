# ADR-003: Audio and Bluetooth stack - PipeWire + WirePlumber, BlueZ, oFono, GStreamer

- Status: Accepted (pending D-09, D-10 confirmation)
- REQ: REQ-029, 032-036, 038-046, 205, 402

## Decision
| Concern | Choice |
|---|---|
| Sound server | PipeWire with WirePlumber policy, single ALSA sink (REQ-205) |
| Arbitration | WirePlumber role-based policy: `alert` > `call` (incl. ringtone) > `prompt` > `media`; alert ducks media -20 dB; alerts never muted (REQ-045, 402) |
| Call vs media | oneo-mediad pauses media on call start, resumes on end (REQ-044) |
| Decoding | GStreamer (mp3, flac, aac via faad/fdk or avdec) -> pipewiresink, role=media (REQ-029) |
| BT host | BlueZ 5; SSP numeric comparison via agent in oneo-phoned; max 5 bonded devices (REQ-038, 039) |
| A2DP sink / AVRCP 1.5 | BlueZ + PipeWire bluez5 module; control/metadata via BlueZ MediaPlayer1 (REQ-032-034) |
| HFP 1.7 HF | oFono for call control; PipeWire bluez5 ofono backend for SCO (mSBC) audio, role=call (REQ-041, 043) |
| PBAP client | obexd (REQ-046) |
| Volume persist | per-role volume stored by oneo-system in /data (REQ-037) |

## Alternatives
| Option | Rejected because |
|---|---|
| PulseAudio | Maintenance mode; weaker policy/latency than PipeWire |
| Raw ALSA + custom mixer | Re-implements ducking/BT routing |
| Proprietary BT stack | Licence cost; BlueZ covers all R1 profiles |

## Consequences
- AAC codec licensing to be checked by release-manager.
- Policy lives in WirePlumber Lua config owned by middleware-engineer; tested on target (integration-test-engineer).
