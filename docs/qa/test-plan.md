# One-O Test Plan (R1 MVP)

Owner: qa-lead. Source: docs/requirements/requirements.md (Ver column: T/A/I/D). Results go to docs/qa/results.md; defects to docs/qa/defects.md.

## 1. Levels

| Level | Scope | Where it runs | Owner |
|---|---|---|---|
| UT Unit | Single class/module, mocks for CAN, D-Bus, BlueZ, audio, filesystem | Host CI | unit-test-engineer |
| IT Integration | Several services over mock backends (signal svc + settings + lockout; media + audio arbiter; BT stack mock); QML via QtTest + Qt Quick Test | Host CI (offscreen Qt) | integration-test-engineer |
| ST System | Full image on target/reference HW with real CAN/BT/USB/display; boot, crash recovery, power loss | Target bench | qa-lead + integration-test-engineer |
| PT Performance | Boot time, latency, fps, memory, 100 h soak | Target bench | perf-engineer |
| SEC Security | Privilege, secure boot, dm-verity, pairing rules, allow-list, threat-model pass | Host + target | security-engineer |
| ACC Acceptance | Demo (D) and inspection (I) items walked per story | Target, product-owner witness | qa-lead |

## 2. Tooling

| Purpose | Tool |
|---|---|
| Unit/integration framework | GoogleTest + GoogleMock |
| Runner / CI entry | CMake + CTest (`ctest --output-on-failure`, labels `unit`, `integration`, `system`, `perf`, `sec`) |
| QML/UI logic | QtTest, Qt Quick Test (`QT_QPA_PLATFORM=offscreen`) |
| Coverage | gcov/lcov (GCC), report in CI artifact |
| Static/dynamic checks | clang-tidy, cppcheck; ASan/UBSan/TSan builds of host tests; valgrind/heaptrack for leaks |
| CAN simulation | SocketCAN `vcan` + mock DBC, `cansend`/canplayer |
| Bluetooth | BlueZ mock + real phone matrix on bench |
| Perf | systemd-analyze, boot log marker, GPU/fps counters, `smem`/`/proc` sampling script |
| Security | lynis/checksec, `veritysetup`, fuzzing of D-Bus/CAN parsers (libFuzzer) |

## 3. Coverage targets

| Metric | Target | Applies to |
|---|---|---|
| Line coverage | >= 80 % overall, >= 90 % for core logic (lockout, audio arbiter, signal validation, settings confirm) | Host UT+IT |
| Branch coverage | >= 70 % core logic | Host UT+IT |
| Requirement coverage | 100 % of Must-story REQs have >= 1 test case (REQ-056); Should REQs covered or waived in results.md | Traceability |
| Safety-critical REQs (048-050, 401, 402, 407, 408) | 100 % branch, plus negative tests | UT+IT+ST |
| Defects at release | 0 open Sev-1/Sev-2; 0 open high security findings (REQ-405) | Release |

## 4. Entry / exit criteria

| Gate | Entry | Exit |
|---|---|---|
| UT/IT (per change) | Code compiles, tech-lead reviewed | All unit+integration tests pass, coverage not below target, no sanitizer errors |
| System test | Image builds (REQ-001), UT/IT green on that commit, test bench ready | All ST cases executed; no open Sev-1/2; Sev-3 have owner and plan |
| Perf | Release-candidate image | REQ-100..106 measured and recorded; soak 100 h clean |
| Release sign-off | ST, PT, SEC exit met; traceability complete | qa-lead sign-off in docs/qa/results.md; assumption-flagged (A:D-xx) REQs either confirmed or recorded as risk |

## 5. REQ to test mapping

Test-case IDs: `<level>-<area>-<nn>` (e.g. UT-LOCK-01). Detailed cases are owned by the level engineers; each must cite its REQ ids in the test name or CTest label. Ver = requirement verification method.

| REQ range | Area | Ver | Test levels | Key checks |
|---|---|---|---|---|
| 001-003, 208 | Image build, recipe, reproducibility, A/B layout | T/I/A | ST, inspection | Clean-checkout build flashes; recipe present; two builds give identical manifest diff; partition table/version metadata |
| 004, 100, 101 | Boot time | T | PT | Boot-time log per build; cold <= 10 s, splash <= 3 s, warm <= 3 s; N=10 runs, report max/p95 |
| 005-007, 107 | Crash supervision | T | IT (systemd unit parse), ST | Kill -SEGV: restart <= 2 s, reason logged, restart limit stops and fault reported, HMI interactive without reboot |
| 109 | Power loss | T | ST | Repeated abrupt power cuts (>= 100 cycles) during write; no FS/settings corruption |
| 008, 009, 108 | Logging, diagnostics | T/D/A | UT (rotation), ST, ACC, analysis | Persist across reboot; size/age rotation; write-rate estimate vs eMMC endurance; diag screen demo |
| 010-014, 102, 103 | Home, navigation, status bar, responsiveness | D/T | QtTest, ACC, PT | Tiles/back/home on every screen; status bar update <= 1 s; first response <= 100 ms; 60 fps during navigation |
| 015, 016, 017-019 | Themes, language, units | D/T/I | QtTest, UT, inspection | Auto theme from signal plus manual override; en-US/de-DE runtime switch; unit switch; no hard-coded strings (lupdate check) |
| 020-022, 203 | Vehicle signal service API | I/T | UT (mock), IT, inspection | Mock/real backend selectable; grep gate: no CAN/D-Bus use in UI code; D-Bus name present |
| 023-025, 201 | Signal display and validity | D/T | UT, IT (vcan), ACC | Speed/gear/door/lamp shown; update <= 200 ms; timeout shows unavailable |
| 026-028, 202, 407 | Settings write path | D/T | UT, IT, ST | Write sent, confirmed by feedback, UI shows actual state; failure/unconfirmed shows error; non-allow-listed write rejected |
| 200 | CAN bus | T | IT (vcan), ST | 500 kbit/s; mock DBC decode/encode round trip; real DBC when supplied |
| 029-031, 207 | USB audio | T/D | IT, ST, ACC | MP3/FLAC/AAC playback; hot insert/remove no restart; browse folder/artist/album |
| 032-034, 204 | Bluetooth audio | T/D | IT (mock), ST (phone matrix) | A2DP stream; AVRCP both directions; metadata shown |
| 035-037, 205 | Now playing, source, volume | D/T/I | QtTest, ST, inspection | Source switch audible <= 2 s; volume persists across reboot; single sink with per-stream volume |
| 038-040, 406 | Pairing | T/I | IT, ST | SSP numeric comparison; 5-device limit (6th handled); auto-reconnect; pairing needs user confirm |
| 041-045, 402 | Calls and audio arbitration | T/D | UT (arbiter), IT, ST | HFP answer/reject; call audio routing; media pause/resume; priority order alert > call > prompt > media; 20 dB duck; alerts never muted |
| 046, 047 | Contacts (Should) | T/D | IT, ACC | PBAP sync on connect; search; dial from contact/log |
| 048-050, 401, 400 | Driving lockout | T/A | UT (state machine), IT, ST, design review | Threshold default 8 km/h, configurable; at/below/above boundary values; speed unavailable means locked; pairing disabled when driving; NHTSA/ISO analysis memo |
| 408 | Service-side lockout | T | UT, IT, SEC-4 | oneo-system/oneo-phoned reject pairing and settings-edit commands while locked, for any caller and any HMI state (direct D-Bus calls bypassing HMI); oneo-vehicled rejects vehicle SetSetting with DrivingLocked while locked; unknown speed = locked; lockout source lost (org.oneo.System gone from the bus) = locked |
| 409 | USB class allow-list | T/I | ST, SEC-6 | HID, serial, gadget fixtures rejected; only MSC accepted; mount options ro,nosuid,nodev,noexec checked on mounted media; unsupported FS types refused |
| 410 | Debug interfaces off | T/I | SEC-9, image inspection | Production image: no UART login, JTAG locked, no adb/ssh/dropbear, no USB gadget, U-Boot console locked; no empty/default root password |
| 051-053, 403, 404 | Platform security | I/T | SEC | Services non-root (ps/unit review); signature verify at boot; dm-verity tamper test fails boot/read; key handling and fallback risk recorded |
| 054, 405 | Threat model, security pass | I/T | SEC | Threat model doc; fuzz/scan results; zero open high findings |
| 406 | Exposed interfaces | I | SEC | Port/bus scan lists only required interfaces |
| 055, 056, 302, 304, 301, 303 | CI and constraints | T/I | CI config review | CTest runs on host with mocks in CI; trace matrix complete; C++17/CMake/Qt/systemd inspected |
| 104-106, 057 | Memory and soak | T/A/I | PT | Idle RSS <= 512 MB; 100 h soak no crash/restart; memory slope below threshold (see 6); results published |
| 206, 300, 305, 306 | HW/scope constraints | I | Inspection | Display/SoC match; radio and camera absent; sources limited to USB+BT |

## 6. Decisions owned by QA

- Memory-leak threshold (REQ-106): linear-fit RSS growth over the 100 h soak <= 1 MB/h and total growth <= 10 % after warm-up (first 2 h excluded). Revisit after the first soak.
- Latency/boot measurements: 10 runs minimum; pass on max, report p95.
- Assumption-flagged REQs (A:D-xx) are tested against the stated value; a changed decision triggers a test-case review, not silent change.
- Excluded from R1 (no tests): radio, rear camera, OTA client.

## 7. Defect handling

See docs/qa/defects.md for severity and workflow. Release gate per section 3.
