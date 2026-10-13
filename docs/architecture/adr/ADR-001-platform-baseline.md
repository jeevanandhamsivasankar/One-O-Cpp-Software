# ADR-001: Platform baseline - Yocto Scarthgap, systemd, Qt 6.8 LTS

- Status: Accepted (pending D-07 confirmation)
- REQ: REQ-001, 003, 100, 102, 103, 206, 300-303

## Context
Need a long-supported OS/toolkit combination for i.MX8M-class SoC with GPU, 60 fps QML at 1280x720, and <= 10 s cold boot.

## Decision
| Item | Choice |
|---|---|
| Yocto | 5.0 Scarthgap LTS (support to 2028), meta-freescale / NXP BSP, own `meta-oneo` layer |
| Init | systemd (required by REQ-005/301), journald, systemd-coredump |
| Qt | Qt 6.8 LTS via meta-qt6; QtQuick, QtQuick Controls, QtDBus, Qt Linguist; platform plugin EGLFS (KMS), no Wayland compositor (single full-screen app) |
| Toolchain | GCC 13 (Scarthgap), C++17, CMake; same CMake builds host (mocks) and target SDK |
| Kernel | NXP LTS kernel from BSP |

## Alternatives
| Option | Rejected because |
|---|---|
| Qt 5.15 | End of open-source support; weaker QML compiler/performance |
| Wayland + Weston | Extra process, memory and boot time; not needed for one app in R1 (revisit for R2 camera overlay) |
| Kirkstone | Older; Scarthgap aligns with Qt 6.8 layer support |

## Consequences
- EGLFS ties HMI to one process owning the display; camera (R2) may need a compositor ADR.
- Qt LGPL compliance (dynamic linking, relinkable) must be checked by release-manager.
