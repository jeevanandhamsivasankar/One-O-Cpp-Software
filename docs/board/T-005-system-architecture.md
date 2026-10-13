# T-005: End-to-end system architecture

- Owner: principal-architect
- Phase: Design
- Reviewer: tech-lead
- Read: docs/requirements/requirements.md, docs/product/decisions.md, this ticket
- Change: docs/architecture/system.md, docs/architecture/adr/, this ticket's Log

## Goal
Define the layered architecture: hardware/SoC, Yocto OS, kernel/drivers, middleware (D-Bus, CAN, audio, BT), C++ core services, Qt/QML HMI; process model, boot sequence, IPC, update path.

## Acceptance criteria
- [ ] system.md with layer + process diagram (Mermaid), component list with owner role, boot sequence vs boot-time REQs.
- [ ] ADRs (adr/ADR-00x-*.md) for key choices (e.g. Qt version, IPC, audio stack, init/systemd, update strategy).
- [ ] Each component traces to REQ-xxx.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
- Status: done - principal-architect - system.md (layers, process model, components+owners+REQ trace, boot budget 7.5 s vs REQ-100) + ADR-001..005 (platform/Qt 6.8, D-Bus IPC, PipeWire/BlueZ audio, process supervision, HAB+verity+A/B RAUC).
- Request: cpp-architect - derive C++ interfaces and D-Bus XML contracts for org.oneo.{VehicleSignals,Media,Phone,System} per ADR-002/004.
- Request: yocto-bsp-lead - confirm partition layout, HAB/FIT chain and boot budget feasibility per ADR-005 and system.md section 4.
- Request: security-engineer - threat model (REQ-054) on process model/D-Bus policy; record no-HAB risk (REQ-404).
- Status: done - principal-architect - aligned system.md section 5 + ADR-005 with T-009 (fit_a/fit_b 2x 32 MB outside verity; verity hash in 2 GB slot, rootfs <= ~1.9 GB; /data ~3.8 GB).
- Status: done - principal-architect - tech-lead review applied: lockout edge oneo-system->oneo-vehicled + ADR-004 Lockout row (enforced by HMI, oneo-phoned, oneo-vehicled; unknown = locked); REQ-408/409/410 traced in section 3; /data ~3.1-3.2 GiB (estimate, verify on board) in system.md + ADR-005.
- Review: changes needed - tech-lead - partition layout/FIT chain now matches yocto.md section 4 and ADR-005 (OK). Fix: (1) REQ-408 gap: vehicle settings writes go to oneo-vehicled, which does not receive lockout; make oneo-system the single lockout authority and add lockout edge S -> V in the section 2 diagram and ADR-004 Lockout row ("HMI, phoned and vehicled enforce; unknown/stale lockout state => locked"); (2) section 3 trace: add REQ-408 to oneo-system, oneo-phoned, oneo-vehicled; REQ-409 to System config (udev/mount rules) and oneo-mediad; REQ-410 to BSP and Partitions/boot chain; (3) /data size: 8 GB eMMC user area is ~7.2-7.3 GiB, so remainder is ~3.1-3.2 GiB with 2 GiB slots - write "remainder (~3.1+ GB, verify on board)" in section 5 and ADR-005.
- Review: approved - tech-lead - re-check: lockout edge S->V, ADR-004 Lockout row (single authority, unknown=locked), REQ-408/409/410 traced in section 3, /data ~3.1-3.2 GiB in system.md + ADR-005.
