# T-006: UX journeys and HMI guidelines

- Owner: ux-lead
- Phase: Design
- Reviewer: tech-lead
- Read: docs/requirements/requirements.md, docs/product/backlog.md, this ticket
- Change: docs/ux/journeys.md, docs/ux/guidelines.md, this ticket's Log

## Goal
Define user journeys and interaction architecture for media, phone, vehicle settings and driving-restricted mode.

## Acceptance criteria
- [ ] journeys.md: navigation map (Mermaid) + one journey per Must story.
- [ ] guidelines.md: touch-target sizes, glance-time rules, driving lockouts, theme/day-night, layout grid for the target display.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
Status: done - ux-lead wrote docs/ux/journeys.md (nav map + J-01..J-09 covering all UX Must stories) and docs/ux/guidelines.md (targets, glance, lockouts, theme, grid). Ready for tech-lead review.
- Review: changes needed (minor) - tech-lead - navigation map, lockout scope and targets consistent with screen specs and REQ-048..050. Fix: (1) journeys.md J-09 step 3 "unlock <= 1 s" conflicts with guidelines hysteresis "unlock after speed <= threshold for 1 s" - reword to "controls unlock 1 s after speed <= threshold (+<= 100 ms render)"; (2) guidelines.md Driving lockouts: add rule for a service-side rejection (REQ-408, race at threshold): control reverts, same "Available when parked" banner, no error toast.
Status: review changes done - J-09 unlock wording aligned to 1 s hysteresis; guidelines.md gained REQ-408 service-rejection rule (revert + 'Available when parked' banner).
- Review: approved - tech-lead - re-check: J-09 step 3 matches 1 s hysteresis; guidelines REQ-408 service-rejection row OK.
