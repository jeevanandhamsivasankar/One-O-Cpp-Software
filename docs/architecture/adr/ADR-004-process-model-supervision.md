# ADR-004: Process model and supervision - per-domain daemons under systemd

- Status: Accepted
- REQ: REQ-005-008, 048-051, 104-109

## Decision
| Item | Choice |
|---|---|
| Split | 5 processes: oneo-hmi, oneo-vehicled, oneo-mediad, oneo-phoned, oneo-system (see system.md section 2) |
| Users | One unprivileged user per process; no root; no capabilities (CAN_RAW sockets need none; can0 bitrate/up set by systemd-networkd) (REQ-051) |
| Hardening | `ProtectSystem=strict`, `ProtectHome=yes`, `NoNewPrivileges=yes`, `PrivateTmp=yes`, `ReadWritePaths=/data/<svc>` |
| Liveness | `Type=notify`, `WatchdogSec=2s`, `Restart=always`, `RestartSec=200ms` -> restart < 2 s (REQ-005, 107) |
| Restart limit | `StartLimitBurst=5`, `StartLimitIntervalSec=60`, `OnFailure=oneo-fault@%n.service` sets fault state on `org.oneo.System` and HMI/diagnostics (REQ-007); limit configurable via drop-in |
| Crash reason | systemd-coredump (compressed, size-capped) + exit status in journal (REQ-006) |
| Logs | journald `Storage=persistent` on /data, `SystemMaxUse=64M`, `MaxRetentionSec=14d`, rate-limited (REQ-008, 108) |
| Settings | oneo-system owns all persistent settings; write = temp + fsync + rename, debounced >= 2 s (REQ-108, 109) |
| Lockout | oneo-system computes `DrivingLocked` from speed (default 8 km/h, configurable; invalid speed => locked); oneo-system is the single decider; enforced by HMI, oneo-phoned, oneo-vehicled; unknown = locked (REQ-048-050, 401, 408) |
| HMI restart | Services keep state; HMI reconnects and rebuilds from properties |

## Alternatives
| Option | Rejected because |
|---|---|
| Single monolith | One fault kills everything; cannot apply least privilege per domain |
| One process per feature (10+) | Memory/boot overhead vs REQ-104 |

## Consequences
- Each daemon needs a D-Bus contract and notify/watchdog integration (cpp-architect provides a common service skeleton).
