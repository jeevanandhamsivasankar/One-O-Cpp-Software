# T-008: C++ software architecture and API headers

- Owner: cpp-architect
- Phase: Design
- Reviewer: tech-lead
- Read: docs/architecture/system.md, docs/architecture/adr/, docs/requirements/requirements.md, this ticket
- Change: docs/architecture/software.md, include/oneo/, this ticket's Log

## Goal
Design C++ modules, public interfaces, threading model, memory ownership and error handling for core, middleware, data, HMI bridge and domain modules.

## Acceptance criteria
- [ ] software.md: module diagram, dependency rules, threading/event-loop model, ownership rules, error-handling policy, CMake target layout.
- [ ] include/oneo/<module>/*.hpp interface headers (pure interfaces, documented, C++17) that compile.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
