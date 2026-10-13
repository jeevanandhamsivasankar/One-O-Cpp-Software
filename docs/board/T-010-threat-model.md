# T-010: Threat model and security requirements

- Owner: security-engineer
- Phase: Design
- Reviewer: tech-lead
- Read: docs/architecture/system.md, docs/requirements/requirements.md, this ticket
- Change: docs/security/threat-model.md, this ticket's Log

## Goal
Threat-model the IVI system (CAN, Bluetooth, USB media, updates, debug ports).

## Acceptance criteria
- [ ] threat-model.md: assets, trust boundaries (diagram), STRIDE threats, mitigations mapped to components and REQ-xxx, secure-boot/signing and hardening checklist for Yocto.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
- Status: done - security-engineer - docs/security/threat-model.md (assets, TB diagram, 20 STRIDE threats->component/REQ, residual risks incl. no-HAB R-01 for REQ-404, Yocto hardening checklist, security test pass SEC-1..10). Also covers T-005 request (process model/D-Bus policy REQ-054).
- Request: system-requirements-engineer - consider explicit REQs for service-side lockout enforcement (T-11), USB class allow-list (T-08), production debug-port lock (T-15).
- Request: yocto-bsp-lead - confirm HAB availability (D-11) to close/keep risk R-01.
- Review: changes needed (minor) - tech-lead - assets, boundaries, STRIDE and hardening consistent with system.md process model, users, D-Bus names and partitions. Fix: (1) section 8 last bullet: replace "Suggest adding T-11, T-08, T-15..." with the accepted REQ-408/409/410; (2) REQ column: T-11 add REQ-408, T-08 add REQ-409, T-15 add REQ-410; (3) T-11 mitigation: add oneo-vehicled (vehicle settings writes) to the services that reject commands while locked, and "unknown lockout state => locked"; (4) T-14: note FIT is on raw fit_a/fit_b outside verity, protected by FIT signature only.
- Status: done - security-engineer - review changes applied: REQ-408/409/410 mapped to T-11/T-08/T-15, vehicled added to lockout (unknown=locked, oneo-system sole authority), T-14 FIT-outside-verity note.
- Review: approved - tech-lead - re-check: T-08/T-11/T-14/T-15 rows and section 8 accepted REQ-408..410 OK.
