# One-O MVP Backlog

Priority: MoSCoW. All listed stories are MVP unless marked [post-MVP]. Format: ID, priority, story, acceptance criteria (AC).

## E1 Platform and boot
- **US-001 (Must)** As an OEM, I want a reproducible Yocto image so that builds are consistent.
  AC: clean build yields a flashable image for the target SoC; app installed via its own recipe.
- **US-002 (Must)** As a driver, I want the HMI up quickly after ignition.
  AC: cold boot to interactive HMI within target in vision.md, measured and logged per build.
- **US-003 (Must)** As an OEM, I want the app supervised so it recovers from crashes.
  AC: systemd restarts app within 2 s; crash reason logged; no restart loop beyond a configured limit.
- **US-004 (Should)** As a technician, I want persistent logs and a diagnostics view.
  AC: logs survive reboot with rotation; diagnostics screen shows versions and service health.

## E2 HMI framework and home
- **US-005 (Must)** As a driver, I want a home screen with tiles for Media, Phone and Settings.
  AC: each tile opens its screen in <= 100 ms response; back/home always reachable.
- **US-006 (Must)** As a driver, I want a persistent status bar (time, connectivity, signal, alerts).
  AC: updates within 1 s of state change.
- **US-007 (Should)** As a driver, I want day/night themes.
  AC: switches automatically via ambient/headlight signal, or manually.
- **US-008 (Should)** As a user, I want language and unit selection.
  AC: at least 2 languages; runtime switch without reboot.

## E3 Vehicle integration (CAN/D-Bus)
- **US-009 (Must)** As a developer, I want a vehicle signal service abstracting CAN and D-Bus.
  AC: C++17 interface with mock and real backends; UI never touches buses directly.
- **US-010 (Must)** As a driver, I want to see vehicle status (speed, gear, door/lamp warnings).
  AC: values shown within 200 ms of signal change; stale signals shown as unavailable.
- **US-011 (Must)** As a driver, I want to change supported vehicle settings (lights, units, climate display).
  AC: change is sent, confirmed by vehicle feedback, and UI reflects actual state; failure shown to user.
- **US-012 (Should)** As a driver, I want a rear-gear camera view trigger. [dependent on hardware; confirm]
  AC: on reverse gear, camera view shown within 500 ms.

## E4 Media
- **US-013 (Must)** As a user, I want to play audio from USB.
  AC: browse by folder/artist/album; MP3, FLAC, AAC play; hot-plug handled.
- **US-014 (Must)** As a user, I want to stream audio over Bluetooth (A2DP/AVRCP).
  AC: play/pause/skip from HMI and phone; metadata shown.
- **US-015 (Must)** As a user, I want a now-playing screen with volume and source switching.
  AC: source switch audible within 2 s; volume persists across reboot.
- **US-016 (Should)** As a user, I want AM/FM radio. [hardware tuner dependent; confirm]
  AC: tune, seek, presets (6).
- **US-017 (Could)** As a user, I want a play queue and shuffle/repeat.
  AC: modes persist per source.

## E5 Phone and connectivity
- **US-018 (Must)** As a driver, I want to pair a phone via Bluetooth.
  AC: pairing with confirmation code; up to 5 paired devices; auto-reconnect to last device.
- **US-019 (Must)** As a driver, I want to make and receive calls hands-free (HFP).
  AC: incoming call screen with answer/reject; call audio routed; media ducks/pauses and resumes.
- **US-020 (Should)** As a driver, I want contacts and call log (PBAP).
  AC: synced on connect; searchable; dial from entry.
- **US-021 (Could)** As a user, I want SMS notifications (MAP). [post-MVP candidate]
  AC: incoming message notice; read-only.

## E6 Driving safety and security
- **US-022 (Must)** As a safety officer, I want distracting functions locked while driving.
  AC: above speed threshold, text entry and list browsing disabled; threshold configurable.
- **US-023 (Must)** As an OEM, I want least-privilege services and a signed image.
  AC: services run as non-root; image signature verified at boot where SoC supports it.
- **US-024 (Should)** As an OEM, I want a threat model and security test pass.
  AC: documented threats with mitigations; no high-severity open findings at release.

## E7 Quality and release
- **US-025 (Must)** As a team, I want automated unit and integration tests in CI.
  AC: CMake tests run on host with mocks; every Must story has traceable tests.
- **US-026 (Must)** As a product owner, I want performance and soak results against vision metrics.
  AC: boot, latency, memory and 100 h soak reported in docs/qa/results.md.

## Epic summary
| Epic | Stories | Must |
|---|---|---|
| E1 Platform and boot | 001-004 | 3 |
| E2 HMI framework | 005-008 | 2 |
| E3 Vehicle integration | 009-012 | 3 |
| E4 Media | 013-017 | 3 |
| E5 Phone | 018-021 | 2 |
| E6 Safety and security | 022-024 | 2 |
| E7 Quality | 025-026 | 2 |

Suggested order: E1 and E3 foundation, then E2, E4, E5, with E6 and E7 running throughout. Could items (US-017, US-021) and US-012/016 are first to cut.

## Open questions
For product-manager:
- Confirm boot targets (cold 10 s, warm 3 s) and target market/OEM.
- Is radio or rear camera in MVP, and does the hardware include a tuner/camera?
- Which languages and regions at launch?
- Is OTA update required for MVP or only the image design to allow it?

For system-requirements-engineer:
- Which CAN signals/DBC and which D-Bus services define the vehicle settings subset?
- Target SoC, RAM and display resolution (drives memory and fps budgets).
- Regulatory driver-distraction standard to follow and speed threshold.
- Audio routing/arbitration requirements (ducking priorities) and Bluetooth profiles required.
- Secure boot and signing capabilities of the SoC.
