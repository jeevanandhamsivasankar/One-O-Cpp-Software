# ADR-002: IPC - D-Bus system bus with `org.oneo.*` service contracts

- Status: Accepted
- REQ: REQ-014, 020-022, 024, 027, 203, 304, 406, 407

## Context
HMI must not touch CAN or D-Bus middleware directly (REQ-022); vehicle access is fronted by `org.oneo.VehicleSignals` (REQ-203); logic must be host-testable (REQ-304).

## Decision
| Item | Choice |
|---|---|
| Transport | D-Bus system bus (dbus-broker), one well-known name per service: `org.oneo.VehicleSignals`, `.Media`, `.Phone`, `.System` |
| Contract | D-Bus introspection XML in repo is the single source of truth; code generated for both sides |
| Service side | sdbus-c++ adapter over a pure C++17 core library (no Qt in daemons) |
| HMI side | QtDBus proxies wrapped in QObject models exposed to QML; QML never sees D-Bus |
| Data flow | Properties + `PropertiesChanged` for state (signals coalesced <= 50 ms); methods for commands returning async result |
| Commands | Vehicle writes: `SetSetting(name, value)` -> validated against allow-list (REQ-407) -> CAN -> confirmed by feedback signal or timeout error (REQ-027/028) |
| Validity | Each signal carries `{value, valid, timestamp}`; vehicled flags invalid after timeout (REQ-025) |
| Access | dbus policy files: only listed users may own names / call methods (REQ-406) |

## Alternatives
| Option | Rejected because |
|---|---|
| Qt Remote Objects / gRPC | Not required by REQ-203; adds stack; D-Bus already needed for BlueZ/oFono |
| In-process (single binary) | Crash in BT/media would take down HMI; violates isolation and least privilege |
| SOME/IP | No Ethernet backbone in R1 |

## Consequences
- D-Bus latency (~1 ms) fits REQ-024 (200 ms) and REQ-014 (1 s).
- Two D-Bus libraries (sdbus-c++, QtDBus); both generated from the same XML to stay in sync.
- Mock backends plug in behind the core library interface (REQ-021), selectable by build option and `--backend=mock|can`.
