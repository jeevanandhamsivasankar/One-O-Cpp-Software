# One-O Vision

## Problem
Drivers juggle phones, aftermarket head units and separate vehicle menus. This is distracting, slow to start and inconsistent. OEMs need a reliable, fast-booting, maintainable IVI platform that unifies media, phone and vehicle settings behind one touch HMI.

## Target users
- Driver: wants quick, glanceable, low-distraction access to media, calls and vehicle settings.
- Front passenger: browses and controls media; no safety-critical access.
- Vehicle OEM / integrator: needs a stable, updatable, testable software base on a custom Yocto image.
- Service technician: needs diagnostics and logs.

## Product goals
1. Fast, dependable IVI: HMI usable within seconds of ignition.
2. One coherent Qt/QML touchscreen experience for media, phone and vehicle settings.
3. Clean C++17 core separated from the UI and from vehicle buses (CAN, D-Bus), so it is testable and portable.
4. Reproducible Yocto image on the target ARM SoC with a path to OTA updates.
5. Driver-distraction safety: restricted interactions while driving.

## MVP scope
In:
- Boot to HMI, home screen, navigation shell, status bar, day/night theme.
- Media: local USB and Bluetooth audio playback, source switching, volume.
- Phone/connectivity: Bluetooth pairing, calls (HFP), contacts and call log (PBAP).
- Vehicle settings: read and set a defined subset (e.g. lights, climate display, units) via CAN/D-Bus gateway; vehicle status display.
- Platform: Yocto image, app recipe, systemd service, logging, crash recovery.
- Basic security (signed image/secure boot per SoC support, least privilege) and driving-restriction lockout.

Out (post-MVP):
- Turn-by-turn navigation and maps, voice assistant, smartphone projection (CarPlay/Android Auto), streaming/online services, OTA backend, app store, multi-user profiles, rear-seat displays, ADAS/safety-critical functions.

## Success metrics
| Metric | MVP target (to confirm) |
|---|---|
| Cold boot to interactive HMI | <= 10 s (splash <= 3 s) |
| Warm/resume to HMI | <= 3 s |
| Touch-to-visual response | <= 100 ms; UI >= 30 fps (target 60) |
| Media start after source select | <= 2 s |
| Bluetooth reconnect to last phone | <= 15 s after HMI ready |
| Crash-free hours (soak) | >= 100 h, no restart loops |
| Idle memory footprint | <= 512 MB (to confirm vs SoC) |
| Requirements with passing tests | 100% of Must stories |
