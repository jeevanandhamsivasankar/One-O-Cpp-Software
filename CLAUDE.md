# One-O C++ Software

Production C++17 application (CMake) deployed on a custom Yocto Linux OS.
The 32-person team is defined as subagents in `.claude/agents/`; roster in `docs/team/roster.md`.

## Orchestration (main session)
Subagents cannot spawn each other, so the main session dispatches them, phase by phase.
Run agents in a phase in parallel when their tickets don't touch the same files.

| Phase | Agents | Exit gate |
|---|---|---|
| 1 Define | product-owner, product-manager, system-requirements-engineer, delivery-manager | requirements.md approved by product-owner |
| 2 Design | principal-architect, cpp-architect, ux-lead, ui-designer, yocto-bsp-lead, security-engineer, qa-lead | headers + system.md reviewed by tech-lead |
| 3 Build - app | app-lead → core-logic, middleware, data, app, qt-qml, domain, additional-senior, junior, intern engineers | code compiles, unit tests pass |
| 3 Build - platform | yocto-build, kernel, hw-integration, linux-systems engineers; devops-engineer | image builds with app recipe |
| 4 Verify | unit-test, integration-test, perf, security engineers; qa-lead | qa-lead sign-off in docs/qa/results.md |
| 5 Release | tech-lead (final review), release-manager, tech-writer, product-owner (acceptance) | tag pushed, CHANGELOG updated |

## Token rules
- Only dispatch an agent whose role is needed for the current ticket; skip idle roles.
- Pass the agent a ticket path (`docs/board/T-xxx.md`), not pasted content.
- Agents reply in ≤5 lines; details live in files. Don't re-read files to double-check an agent's work; review via tech-lead.
- Use haiku/sonnet agents for routine work; reserve opus agents (architects, tech-lead) for design and review.

## Board
- Tickets: `docs/board/T-<nnn>-<slug>.md` from `docs/board/TEMPLATE.md`. One owner per ticket.
- `docs/board/status.md` is the single source of progress (delivery-manager owns it).
- Every code change: owner → tech-lead review → qa (tests) → done.
