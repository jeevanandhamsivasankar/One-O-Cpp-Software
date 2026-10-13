# T-012: Phase 2 design review

- Owner: tech-lead
- Phase: Design
- Reviewer: -
- Read: docs/architecture/, include/oneo/, docs/platform/yocto.md, docs/security/threat-model.md, docs/ux/, docs/qa/test-plan.md, this ticket
- Change: docs/standards/coding.md, review lines in T-005..T-011 Logs, this ticket's Log

## Goal
Review all Phase 2 outputs for consistency and buildability; write coding standards (Phase 2 exit gate).

## Acceptance criteria
- [ ] include/oneo headers compile (g++/clang -fsyntax-only or CMake) - or note why not possible here.
- [ ] Review line per ticket T-005..T-011: approved or changes needed.
- [ ] docs/standards/coding.md written.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
Note (orchestrator): also decide on security-engineer proposals in T-010 Log (new REQs: service-side lockout enforcement, USB class allow-list, production debug-port lock) - accept into Phase 3 tickets or defer; and confirm T-009 partition change (FIT outside verity rootfs) is reflected in system.md.
Decision (user): security proposals ACCEPTED into Phase 3 as REQ-408..410 (added by system-requirements-engineer). Check that cpp-architect interfaces allow service-side lockout enforcement.
- Status: partial - tech-lead - pass 1: reviewed T-005/006/007/009/010/011 (all changes needed, minor except T-005 lockout gap and T-007 REQ-408..410 mapping); docs/standards/coding.md written. T-009 FIT-outside-verity change is reflected in system.md section 5 and ADR-005 (confirmed). Security proposals REQ-408..410 accepted per user; tech-lead decision: oneo-system is the single lockout authority, oneo-vehicled/phoned/system reject edits while locked (unknown => locked). Pending: T-008 review + header compile check, then lockout-interface check.
- Review: Phase 2 gate NOT PASSED (blocked on T-008) - tech-lead - headers compile clean (AC1 met, strict flags); review lines in T-005..T-011 (AC2 met); docs/standards/coding.md written and aligned with T-008 (AC3 met). Approved: T-005, T-006, T-010, T-011. Changes needed: T-008 (REQ-408 interfaces: core ILockoutSource injected into vehicle/phone cores, DrivingLocked on VehicleSignals.SetSetting, per-key System lockout rule, phone method list, software.md section 8 flags/GoogleTest) - BLOCKING per user decision; T-007 (REQ-408 row add vehicled) and T-009 (REQ-409 USB wording) - one-line, non-blocking but required before gate close. Gate passes when those three log done; tech-lead re-checks by grep + header compile.
- Blocked: cpp-architect - T-008 interfaces must allow service-side lockout enforcement (REQ-408) before Phase 2 exit; see T-008 Review line.
- Review: Phase 2 gate PASSED - tech-lead - all ACs met: 20 include/oneo headers compile clean (clang++ -std=c++17 -fsyntax-only, coding.md warning set + -Werror, standalone and combined); T-005..T-011 all approved; docs/standards/coding.md written and aligned with software.md (target naming per software.md section 8). REQ-408 service-side lockout supported by interfaces (core::ILockoutSource, DrivingLocked errors, per-key rule). Decision: oneo-phone may set phone.* keys (uid-checked key scope + SEC-2 negative test). Earlier Blocked line resolved. Carry to Phase 3: open D-xx assumptions (D-06 DBC, D-07 board, D-11 HAB -> risk R-01), boot budget unmeasured, root CMakeLists replaced by software.md layout (app-lead).
