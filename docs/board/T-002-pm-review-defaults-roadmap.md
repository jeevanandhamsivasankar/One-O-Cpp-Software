# T-002: Review T-001, resolve open questions with defaults, roadmap

- Owner: product-manager
- Phase: Define
- Requirement: -
- Reviewer: product-owner
- Read: docs/product/vision.md, docs/product/backlog.md (Open questions section), this ticket
- Change: docs/product/roadmap.md, docs/product/decisions.md, this ticket's Log

## Goal
The user said "use defaults". Answer ALL open questions in docs/product/backlog.md (both the product-manager and system-requirements-engineer lists) with typical, realistic IVI defaults. Mark every answer as `ASSUMPTION (confirm with customer)`. Then write the release roadmap.

## Acceptance criteria
- [ ] docs/product/decisions.md: one row per open question → default answer + short rationale (e.g. SoC/RAM/display, boot targets, radio/camera, OTA, languages, CAN/D-Bus subset, distraction standard + speed threshold, audio priorities, BT profiles, secure boot).
- [ ] docs/product/roadmap.md: MVP + 2 later releases, with which US-xxx go in each, and release objectives.
- [ ] Review line for T-001 appended to docs/board/T-001-product-vision-backlog.md Log (accept, or list changes needed).

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
Status: done - decisions.md (13 defaults, all ASSUMPTION), roadmap.md (R1 MVP, R2, R3) written; T-001 review appended (accept).
