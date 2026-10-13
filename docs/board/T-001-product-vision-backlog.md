# T-001: Product vision and initial backlog

- Owner: product-owner
- Phase: Define
- Requirement: -
- Reviewer: product-manager
- Read: CLAUDE.md, docs/board/T-001-product-vision-backlog.md
- Change: docs/product/vision.md, docs/product/backlog.md, this ticket's Log

## Goal
Define the vision and a prioritised MVP backlog for **One-O**, an in-vehicle infotainment (IVI) system: a Qt/QML touchscreen HMI running a C++17 application on a custom Yocto Linux image (ARM SoC), covering media, phone/connectivity and vehicle settings via CAN/D-Bus.

## Acceptance criteria
- [ ] docs/product/vision.md: problem, target users, product goals, scope (in / out for MVP), success metrics (incl. boot-to-HMI time).
- [ ] docs/product/backlog.md: epics → user stories with IDs (US-xxx), MoSCoW priority and acceptance criteria per story; MVP stories marked.
- [ ] Open questions listed for product-manager and system-requirements-engineer.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
Status: done - vision.md and backlog.md written (7 epics, 26 stories, open questions listed for product-manager and system-requirements-engineer).
Review: product-manager - accept. Minor notes: US-021 (MAP) is Could but listed "MVP"; roadmap places it in R2. US-012/US-016 moved to R2 per docs/product/decisions.md. No rework needed.
