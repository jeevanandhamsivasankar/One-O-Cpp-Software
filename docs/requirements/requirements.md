# One-O System Requirements (R1 MVP)

Scope: R1 stories per docs/product/roadmap.md (US-012, 016, 017, 021 excluded). Verification: T=Test, A=Analysis, I=Inspection, D=Demo.
Flag `[A:D-xx]` = depends on an ASSUMPTION decision in docs/product/decisions.md (confirm with customer). Priority follows source story (Must/Should).

## 1. Functional

| ID | Requirement | Source | Ver | Flag |
|---|---|---|---|---|
| REQ-001 | The build system shall produce a flashable Yocto image for the target SoC from a clean checkout. | US-001 | T | A:D-07 |
| REQ-002 | The application shall be installed in the image through its own Yocto recipe. | US-001 | I | |
| REQ-003 | The build shall be reproducible: identical inputs yield an image with identical content manifest. | US-001 | A | |
| REQ-004 | The system shall measure cold-boot time to interactive HMI and log it for every build. | US-002 | T | A:D-01 |
| REQ-005 | systemd shall supervise the application and restart it within 2 s of a crash. | US-003 | T | |
| REQ-006 | The system shall log the crash reason on each application failure. | US-003 | T | |
| REQ-007 | The system shall stop automatic restarts after a configurable restart limit is exceeded and report the fault state. | US-003 | T | |
| REQ-008 | Logs shall persist across reboot with size/age rotation. (Should) | US-004 | T | |
| REQ-009 | A diagnostics screen shall show software versions and service health. (Should) | US-004 | D | |
| REQ-010 | The home screen shall provide tiles for Media, Phone and Settings. | US-005 | D | |
| REQ-011 | Each home tile shall open its screen with first visual response <= 100 ms. | US-005 | T | A:D-07 |
| REQ-012 | Back and Home controls shall be reachable from every screen. | US-005 | D | |
| REQ-013 | A persistent status bar shall show time, connectivity, signal and alerts. | US-006 | D | |
| REQ-014 | The status bar shall reflect a state change within 1 s. | US-006 | T | |
| REQ-015 | The HMI shall provide day and night themes. (Should) | US-007 | D | |
| REQ-016 | The theme shall switch automatically from the ambient/headlight signal, with a manual override. (Should) | US-007 | T | A:D-06 |
| REQ-017 | The HMI shall support English (en-US) and German (de-DE) with runtime switching without reboot. (Should) | US-008 | T | A:D-04 |
| REQ-018 | The HMI shall support metric and imperial unit selection at runtime. (Should) | US-008 | T | A:D-04 |
| REQ-019 | All user-visible strings shall be externalised to translation catalogues. (Should) | US-008 | I | A:D-04 |
| REQ-020 | A vehicle signal service shall expose a C++17 interface abstracting CAN and D-Bus. | US-009 | I | |
| REQ-021 | The vehicle signal service shall provide a mock backend and a real backend selectable at build/run time. | US-009 | T | A:D-06 |
| REQ-022 | UI code shall not access CAN or D-Bus directly; all vehicle access shall go through the vehicle signal service. | US-009 | I | |
| REQ-023 | The HMI shall display vehicle speed, gear, door-open and lamp warnings. | US-010 | D | A:D-06 |
| REQ-024 | Displayed vehicle values shall update within 200 ms of signal change. | US-010 | T | A:D-06 |
| REQ-025 | A signal not received within its validity timeout shall be shown as unavailable. | US-010 | T | |
| REQ-026 | The HMI shall allow setting lighting mode, units and climate display unit/mode. | US-011 | D | A:D-06 |
| REQ-027 | A setting change shall be sent to the vehicle, confirmed by vehicle feedback, and the UI shall show the actual vehicle state. | US-011 | T | |
| REQ-028 | The HMI shall show an error to the user when a setting change fails or is unconfirmed. | US-011 | T | |
| REQ-029 | The system shall play USB audio in MP3, FLAC and AAC formats. | US-013 | T | A:D-13 |
| REQ-030 | The media UI shall allow browsing USB content by folder, artist and album. | US-013 | D | |
| REQ-031 | USB device insertion and removal shall be handled at runtime without restart. | US-013 | T | |
| REQ-032 | The system shall stream Bluetooth audio via A2DP sink. | US-014 | T | A:D-10 |
| REQ-033 | The HMI shall control Bluetooth playback (play/pause/skip) via AVRCP, and the phone shall also be able to control it. | US-014 | T | A:D-10 |
| REQ-034 | The HMI shall display Bluetooth track metadata. | US-014 | D | A:D-10 |
| REQ-035 | A now-playing screen shall show track info, volume and source selection (USB, Bluetooth). | US-015 | D | A:D-13 |
| REQ-036 | A source switch shall be audible within 2 s. | US-015 | T | |
| REQ-037 | Volume shall persist across reboot. | US-015 | T | A:D-09 |
| REQ-038 | The system shall pair phones using Secure Simple Pairing with numeric-comparison confirmation code. | US-018 | T | A:D-10 |
| REQ-039 | The system shall store up to 5 paired devices. | US-018 | T | A:D-10 |
| REQ-040 | The system shall auto-reconnect to the last connected device. | US-018 | T | |
| REQ-041 | The system shall support hands-free calling via HFP 1.7 (hands-free unit role). | US-019 | T | A:D-10 |
| REQ-042 | An incoming call screen shall offer answer and reject. | US-019 | D | |
| REQ-043 | Call audio shall be routed to vehicle speakers and microphone. | US-019 | T | |
| REQ-044 | Media shall pause during a call and resume after it ends. | US-019 | T | A:D-09 |
| REQ-045 | The system shall arbitrate audio by priority: (1) alerts, (2) call/ringtone, (3) system prompts, (4) media; alerts shall duck media by 20 dB. | US-019, US-015 | T | A:D-09 |
| REQ-046 | The system shall sync contacts and call log via PBAP on phone connect. (Should) | US-020 | T | A:D-10 |
| REQ-047 | Contacts shall be searchable and a call shall be dialable from a contact or log entry. (Should) | US-020 | D | |
| REQ-048 | Above the speed threshold, the HMI shall disable text entry, long-list browsing, pairing and settings editing. | US-022 | T | A:D-08 |
| REQ-049 | The lockout speed threshold shall default to 8 km/h and be configurable. | US-022 | T | A:D-08 |
| REQ-050 | If vehicle speed is unavailable, the HMI shall treat the vehicle as driving (locked). | US-022 | T | |
| REQ-051 | Application services shall run as non-root users with least privilege. | US-023 | I | |
| REQ-052 | The image signature shall be verified at boot where the SoC supports it. | US-023 | T | A:D-11 |
| REQ-053 | The rootfs shall be integrity-protected using dm-verity. | US-023 | T | A:D-11 |
| REQ-054 | A threat model with mitigations shall be documented and a security test pass executed. (Should) | US-024 | I | |
| REQ-055 | Automated unit and integration tests shall run in CI on the host using mocks via CMake/CTest. | US-025 | T | |
| REQ-056 | Every Must story shall have at least one traceable test. | US-025 | I | |
| REQ-057 | Boot, latency, memory and 100 h soak results shall be reported in docs/qa/results.md. | US-026 | I | |

## 2. Non-functional

| ID | Requirement | Source | Ver | Flag |
|---|---|---|---|---|
| REQ-100 | Cold boot to interactive HMI shall take <= 10 s (splash <= 3 s). | US-002 | T | A:D-01 |
| REQ-101 | Warm boot/resume to interactive HMI shall take <= 3 s. | US-002 | T | A:D-01 |
| REQ-102 | Touch-to-visual response shall be <= 100 ms for all primary interactions. | US-005 | T | A:D-07 |
| REQ-103 | The UI shall render at 60 fps on the 1280x720 display during normal navigation. | US-005 | T | A:D-07 |
| REQ-104 | Idle memory footprint shall be <= 512 MB of 2 GB. | US-026 | T | A:D-12 |
| REQ-105 | The system shall run 100 h of soak test without a crash or unplanned restart. | US-026 | T | |
| REQ-106 | Memory growth during soak shall be bounded (no leak trend beyond a threshold defined by qa-lead). | US-026 | A | |
| REQ-107 | The system shall recover from an application crash to an interactive HMI within 2 s plus HMI start time, without a reboot. | US-003 | T | |
| REQ-108 | Persistent storage writes (logs, settings) shall be rate-limited and rotated to protect eMMC endurance. | US-004 | A | A:D-07 |
| REQ-109 | The system shall survive abrupt power loss without filesystem or settings corruption. | US-003 | T | |

## 3. Interfaces

| ID | Requirement | Source | Ver | Flag |
|---|---|---|---|---|
| REQ-200 | CAN: the system shall use one CAN bus at 500 kbit/s with an OEM-supplied DBC; a mock DBC shall be used for development. | US-009 | T | A:D-06 |
| REQ-201 | CAN: the system shall read speed, gear, door-open, lamp warnings, ignition state and ambient/headlight status. | US-010 | T | A:D-06 |
| REQ-202 | CAN: the system shall write lighting mode, units and climate display unit/mode. | US-011 | T | A:D-06 |
| REQ-203 | D-Bus: the service `org.oneo.VehicleSignals` on the system bus shall front the CAN gateway for the HMI. | US-009 | I | A:D-06 |
| REQ-204 | Bluetooth: the system shall support BT 5.0 classic + LE with profiles A2DP sink, AVRCP 1.5, HFP 1.7 and PBAP client. | US-014/018/019/020 | T | A:D-10 |
| REQ-205 | Audio: a single audio sink shall be used with per-stream volume control. | US-015 | I | A:D-09 |
| REQ-206 | Display: the HMI shall target a 10.25 in 1280x720 capacitive touchscreen at 60 Hz using OpenGL ES. | US-005 | I | A:D-07 |
| REQ-207 | USB: the system shall mount USB mass storage for MP3, FLAC and AAC playback. | US-013 | T | A:D-13 |
| REQ-208 | Image update: partition layout shall provide A/B rootfs and version metadata to allow later OTA (no OTA client in R1). | US-001 | I | A:D-05 |

## 4. Constraints

| ID | Requirement | Source | Ver | Flag |
|---|---|---|---|---|
| REQ-300 | Hardware reference: ARM Cortex-A quad-core i.MX8M-class SoC with GPU, 2 GB LPDDR4, >= 8 GB eMMC. | US-001 | I | A:D-07 |
| REQ-301 | The OS shall be a custom Yocto Linux image with systemd. | US-001, US-003 | I | |
| REQ-302 | Application code shall be C++17 built with CMake. | US-025 | I | |
| REQ-303 | The HMI shall be implemented with Qt/QML. | US-005 | I | |
| REQ-304 | Business logic shall be testable on the host without target hardware. | US-025 | T | |
| REQ-305 | Radio and rear camera are excluded from R1 (deferred to R2). | US-016, US-012 | I | A:D-02, D-03 |
| REQ-306 | MVP media sources shall be limited to USB audio and Bluetooth audio. | US-013/014 | I | A:D-13 |

## 5. Safety and security

| ID | Requirement | Source | Ver | Flag |
|---|---|---|---|---|
| REQ-400 | Driver-distraction design shall follow NHTSA Visual-Manual Driver Distraction Guidelines and ISO 15005/15007 principles. | US-022 | A | A:D-08 |
| REQ-401 | Bluetooth pairing shall be disabled while driving. | US-022 | T | A:D-08 |
| REQ-402 | Safety alerts shall take highest audio priority and never be muted by media or calls. | US-019 | T | A:D-09 |
| REQ-403 | Image signing keys shall be held by the OEM release process; the image shall carry a verifiable signature. | US-023 | I | A:D-11 |
| REQ-404 | If the SoC lacks secure-boot support, signed images shall be verified at update time and the gap recorded as a documented risk. | US-023 | I | A:D-11 |
| REQ-405 | The release shall have no open high-severity security findings. | US-024 | T | |
| REQ-406 | Only required network/bus interfaces shall be exposed; Bluetooth pairing shall require user confirmation. | US-023, US-018 | I | |
| REQ-407 | Vehicle write commands shall be validated by the vehicle signal service against an allow-list of settable signals. | US-011, US-023 | T | A:D-06 |
| REQ-408 | Driving lockout shall be enforced service-side: services (e.g. oneo-system, oneo-phoned) shall reject pairing and settings-edit commands received while locked, regardless of the caller or HMI state. | US-022, threat T-11 (also T-01) | T (SEC-4) | A:D-08 |
| REQ-409 | USB shall use a device-class allow-list limited to Mass Storage (MSC); all other classes (HID, serial, gadget, etc.) shall be rejected, and USB media shall be mounted ro,nosuid,nodev,noexec with limited filesystem types. | US-013, US-023, threat T-08 | T (SEC-6) | A:D-13 |
| REQ-410 | In production images, debug interfaces (UART console login, JTAG, adb/ssh/dropbear, USB gadget, U-Boot console) shall be disabled or locked, with no empty or default root password. | US-023, threat T-15 | T (SEC-9), I | A:D-11 |
