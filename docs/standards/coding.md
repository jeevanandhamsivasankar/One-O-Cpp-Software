# One-O Coding Standards (C++17)

Owner: tech-lead. Applies to all code under `src/`, `include/`, `tests/`, `qml/` and CMake files. Deviations need a one-line justification in the code (`// NOLINT(<check>): <reason>`) and tech-lead approval in the ticket. Where a rule conflicts with an interface already published in `include/oneo/` (T-008), the header wins and this file is updated.

## 1. Language and toolchain
- C++17 exactly (`CMAKE_CXX_STANDARD 17`, `CMAKE_CXX_STANDARD_REQUIRED ON`, `CMAKE_CXX_EXTENSIONS OFF`). No compiler extensions, no C++20 features via headers or macros.
- Must compile warning-free with clang++ (host, llvm-mingw) and GCC 13 (Yocto Scarthgap): `-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual`. CI builds with `-Werror`.
- Formatting: clang-format (LLVM base, 4-space indent, 100 columns, `PointerAlignment: Left`). Static analysis: clang-tidy (`bugprone-*`, `cppcoreguidelines-*`, `modernize-*`, `performance-*`, `readability-*` minus noisy checks listed in `.clang-tidy`) and cppcheck. Both files are added by app-lead in Phase 3.
- Qt 6.8 only in the HMI (`oneo-hmi`) and in thin Qt-based adapters if any. Core libraries (`oneo_core`, `oneo_data`, `oneo_*_core`) never include Qt or D-Bus headers (system.md section 1, REQ-055, REQ-304).

## 2. Layout and naming
| Item | Rule | Example |
|---|---|---|
| Namespaces | `oneo::<component>` (`vehicle`, `media`, `phone`, `system`, `hmi`, `common`); `detail` for internals; no `using namespace` in headers | `oneo::vehicle::SignalCache` |
| Files | `snake_case.hpp` / `.cpp`; one main class per file; public headers in `include/oneo/<component>/`, private in `src/<component>/` | `signal_cache.hpp` |
| Types, enums, concepts | `PascalCase` | `LockoutState` |
| Functions, methods, variables | `camelCase` | `currentSpeed()` |
| Members | `camelCase_` (trailing underscore) | `threshold_` |
| Constants | `kPascalCase` (`inline constexpr`) | `kDefaultLockoutKph` |
| Enumerators | `PascalCase`, `enum class` only, explicit underlying type when on the wire (matches `include/oneo` and `org.oneo.Error.*` names) | `Gear::Reverse`, `ErrorCode::DrivingLocked` |
| Macros | `ONEO_UPPER_CASE`; avoid except for platform guards and logging | `ONEO_HAS_DBUS` |
| Interfaces | `I` prefix, pure virtual, virtual dtor, no data | `IVehicleSignals` |
| Units | Unit in the name or a strong type; never a bare `int` speed | `speedKmh`, `std::chrono::milliseconds` |
| Tests | `<unit>_test.cpp`; test names `Unit_Condition_Expected` and the REQ id in the CTest label | `Lockout_SpeedUnavailable_Locked` |

- Headers: `#pragma once`; include what you use; order: own header, C++ std, third-party, `oneo/`. Forward-declare where it avoids a heavy include.
- D-Bus names, object paths and interface names come from one constants header generated from or matching the XML contracts; never string literals scattered in code.

## 3. Error handling
- Expected, recoverable failures (signal unavailable, write not confirmed, file missing, peer disconnected, command rejected by lockout) are returned as values: `oneo::core::Result<T>` (sync) or `oneo::core::Completion<T>` (async, invoked once on the loop thread) carrying `core::Error{code, message}` (software.md section 6; C++17 has no `std::expected`). `std::optional<T>` only when "absent" is the only failure. Use the shared `core::ErrorCode` set (1:1 with `org.oneo.Error.*`); add a code there rather than inventing per-component codes. Error messages are diagnostic only, never shown to users.
- Exceptions only for programming errors and unrecoverable startup failures; they never cross a D-Bus adapter, a thread boundary, a callback into Qt, or a C API. Every thread entry point and adapter method catches, logs and converts.
- `[[nodiscard]]` on every function returning a result/error. Ignoring one requires `static_cast<void>` plus a comment.
- No `assert` with side effects; `assert` only for invariants. Safety logic (lockout, audio priority, write allow-list) never relies on asserts: it checks and fails safe.
- Fail safe: unknown or stale input means the conservative state (speed unavailable => locked, REQ-050; unknown lockout state => locked, REQ-408; unknown write target => rejected, REQ-407).
- Validate everything at trust boundaries (CAN frames, D-Bus arguments, BT/AVRCP/vCard metadata, USB file names/tags): length limits, range checks, UTF-8 validation (threat-model T-01, T-06, T-08, T-10).

## 4. Ownership and resources
- RAII for every resource (fds, sockets, D-Bus connections, mounts, threads, timers). No naked `new`/`delete`; no `malloc`.
- `std::unique_ptr` is the default owner; `std::shared_ptr` only when ownership is genuinely shared and documented in the class comment. Non-owning access by reference, or raw pointer/`std::weak_ptr` when it may be null or outlive.
- Pass by `const&` for read-only non-trivial types, by value for sink parameters (then `std::move`), `std::string_view`/span-like views only for non-retained arguments.
- Rule of zero; if a class owns a resource directly, rule of five with explicitly deleted or defaulted members. Polymorphic bases: public virtual dtor or protected non-virtual.
- Dependency injection through constructor interfaces (`IVehicleSignals&`, `IClock&`, `IStorage&`) so cores run with mocks on host. No singletons or mutable globals; constants are `constexpr`/`inline constexpr`.
- Bounded resources: every queue, cache, index and buffer has a documented upper bound (threat-model T-03, T-09; REQ-104). Avoid allocation in hot paths (CAN decode, audio callbacks).

## 5. Threading and concurrency
- Each service runs one event loop thread (the adapter's main loop) that owns the core state. Core classes are single-threaded by default and documented as such; cross-thread work is posted onto the owning loop, not shared under locks.
- Extra threads only for blocking I/O (USB scan, PBAP sync, file writes) and they communicate by message posting. Use `std::thread`/`std::jthread`-style wrappers that join in the destructor; no detached threads.
- If shared state is unavoidable: `std::mutex` + `std::scoped_lock`, never hold a lock while calling callbacks, D-Bus, logging sinks or I/O; lock ordering documented. `std::atomic` only for flags/counters.
- Callbacks must state on which thread they run. Qt objects are touched only on their thread (`QMetaObject::invokeMethod` with queued connection to cross).
- Time: `std::chrono::steady_clock` for timeouts and validity (via injected `IClock`); wall clock only for display/logs. No `sleep` for synchronisation in production or tests.
- TSan host build must be clean (test-plan section 2).

## 6. Logging
- One logging facade in `oneo::common` (Phase 3) that writes to journald on target (sd-journal, structured fields `ONEO_COMPONENT`, `ONEO_REQ` where relevant) and to stderr on host. No `printf`/`std::cout` in production code.
- Levels: `error` (needs action / feature lost), `warn` (degraded, recovered), `info` (state changes: boot markers, pairing, update, USB mount, lockout transitions, policy denials - threat-model T-19), `debug` (off in production builds).
- Never log PII or secrets: no phone numbers, contact names, BT link keys, MAC addresses in full (last 2 bytes only), media file paths from USB beyond the file name (threat-model T-05).
- Rate-limit repeating messages (per-site limiter) to protect eMMC (REQ-108). Never log per CAN frame or per audio buffer at `info` or above.
- Boot marker `ONEO_BOOT_INTERACTIVE` (system.md section 4) is emitted only by oneo-hmi, once.

## 7. Platform code and CMake guards
- Linux-only code (D-Bus via sd-bus/QtDBus, SocketCAN, systemd notify/watchdog, sd-journal, udev, BlueZ/oFono, PipeWire/GStreamer) lives only in adapter/backend directories (`src/<component>/linux/`) and is built only under:
  ```cmake
  add_library(oneo_vehicle_mock STATIC src/vehicle/mock/mock_backend.cpp)   # all hosts
  target_link_libraries(oneo_vehicle_mock PUBLIC oneo_vehicle_core)
  if(UNIX AND NOT APPLE)
    add_library(oneo_vehicle_can STATIC src/vehicle/linux/socketcan_channel.cpp)
    target_link_libraries(oneo_vehicle_can PUBLIC oneo_vehicle_core)
    add_executable(oneo-vehicled src/vehicle/main.cpp)
    target_link_libraries(oneo-vehicled PRIVATE oneo_vehicle_can oneo_vehicle_mock oneo_vehicle_dbus)
  endif()
  ```
  Target layout is defined in software.md section 8 (Linux backends, D-Bus adapters and daemons guarded; cores, data, mocks and `oneo_tests` built everywhere).
- Every Linux backend has a host stub or mock implementing the same interface (`src/<component>/mock/` or `tests/fakes/`) so the Windows host build and all unit tests pass (CLAUDE.md Build). `#ifdef` inside core logic is forbidden; selection happens in CMake or at the composition root (`main.cpp`).
- `find_package` for Linux-only deps (libsystemd, Qt DBus, PipeWire) only inside the guard. The host build must configure with only CMake, clang++ and GoogleTest.
- Targets (software.md section 8 is authoritative): library targets `oneo_<module>` / `oneo_<svc>_core` / `oneo_<svc>_<backend>` (snake_case), executables named like their systemd unit (`oneo-vehicled`, `oneo-hmi`), and one shared host test executable `oneo_tests` whose tests are registered per test with `gtest_discover_tests` and labelled with level + REQ ids (section 8), so `ctest -L` can select by core or REQ. Use `target_*` commands only; no global `include_directories`/`add_definitions`. Warnings set through an `oneo_warnings` INTERFACE target.
- Paths: no hard-coded absolute paths; `/data/...` and `/media/usb` come from configuration with host-test overrides.
- Security hardening of units/policies (ADR-004, threat-model H9-H11) is part of the recipe/unit files, not code, but code must not require capabilities, root, or writes outside `/data` and its own runtime directory.

## 8. Testing
- GoogleTest + GoogleMock for C++ cores; QtTest / Qt Quick Test (offscreen) for HMI logic (test-plan section 2). Every new core class ships with unit tests in the same change.
- Tests are registered with CTest and labelled with level (`unit`, `integration`, ...) and REQ ids (e.g. `LABELS "unit;REQ-048;REQ-408"`) so traceability can be generated (REQ-056).
- Coverage targets per test-plan section 3 (>= 90 % lines and 100 % branches for lockout, audio arbiter, signal validation, write allow-list).
- Tests are deterministic: inject clocks, no real sleeps, no network, no dependence on test order; temp files via a fixture under the build dir.
- Safety and security rules get negative tests: below/at/above threshold, speed unavailable, service-side rejection while locked (REQ-408), non-allow-listed write (REQ-407), malformed input.
- Host CI runs ASan+UBSan and TSan builds of the tests; any finding fails the change.

## 9. Review checklist (tech-lead)
1. Builds on host with clang++ warning-free; tests added and pass; labels carry REQ ids.
2. No Qt/D-Bus/Linux headers in core libraries; Linux code behind the CMake guard with a host stub.
3. Results checked, fail-safe defaults, inputs validated at boundaries.
4. Ownership clear (no naked new, bounded containers), threading documented.
5. Logs: right level, no PII, rate-limited.
6. Naming/format per this file; public header changes match the D-Bus XML contract.
