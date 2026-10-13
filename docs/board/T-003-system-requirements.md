# T-003: System requirements and traceability

- Owner: system-requirements-engineer
- Phase: Define
- Requirement: -
- Reviewer: product-owner (approval = Phase 1 exit gate)
- Read: docs/product/backlog.md, docs/product/decisions.md, docs/product/roadmap.md, this ticket
- Change: docs/requirements/requirements.md, docs/requirements/traceability.md, this ticket's Log

## Goal
Derive numbered, testable system requirements for the MVP from the backlog and the default decisions.

## Acceptance criteria
- [ ] requirements.md: REQ-xxx grouped as Functional, Non-functional (performance, boot, memory, reliability), Interfaces (CAN, D-Bus, Bluetooth, audio, display), Constraints (SoC, Yocto, C++17, Qt), Safety & Security. Each requirement: ID, statement ("shall"), source US-xxx, verification method (Test/Analysis/Inspection/Demo).
- [ ] traceability.md: US-xxx → REQ-xxx matrix; every MVP story covered.
- [ ] Requirements based on ASSUMPTION decisions are flagged.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
Status: done - requirements.md (REQ-001..407, assumptions flagged A:D-xx) and traceability.md written; all 22 R1 stories covered. Awaiting product-owner review (Phase 1 gate).
