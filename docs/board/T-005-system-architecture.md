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
