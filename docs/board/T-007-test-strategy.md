# T-007: Test strategy and plan

- Owner: qa-lead
- Phase: Design
- Reviewer: tech-lead
- Read: docs/requirements/requirements.md, docs/requirements/traceability.md, this ticket
- Change: docs/qa/test-plan.md, docs/qa/defects.md, this ticket's Log

## Goal
Define test levels, tools, coverage targets and acceptance tests for the MVP.

## Acceptance criteria
- [ ] test-plan.md: unit/integration/system/perf/security levels, tooling (GoogleTest, CTest, QtTest), coverage target, entry/exit criteria, REQ → test-case mapping.
- [ ] defects.md: severity scale and defect workflow.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
Status: done - docs/qa/test-plan.md and docs/qa/defects.md written; REQ-to-test mapping by range; REQ-106 leak threshold set (1 MB/h).
Status: done - review changes applied: REQ-408/409/410 rows added to test-plan.md section 5; REQ-408 added to safety-critical row in section 3.
Status: done - REQ-408 row extended: oneo-vehicled SetSetting rejects with DrivingLocked; lockout source lost (org.oneo.System gone) = locked.
- Review: changes needed - tech-lead - levels, tooling, coverage and gates OK; all REQ-001..407 mapped. Fix: section 5 add rows REQ-408 (UT lockout service-side, IT D-Bus call while locked, SEC-4), REQ-409 (ST/SEC-6 with HID/serial/gadget fixtures, mount option check), REQ-410 (SEC-9 + image inspection: no getty/ssh/dropbear/adb, U-Boot console off, no empty root password); section 3 safety-critical row add REQ-408.
- Review: changes needed (one line) - tech-lead - REQ-408/409/410 rows and safety-critical REQ-408 OK. Fix: REQ-408 row key checks list only oneo-system/oneo-phoned - add oneo-vehicled rejecting vehicle SetSetting while locked (DrivingLocked), and "lockout source lost (org.oneo.System gone) = locked".
- Review: approved - tech-lead - re-check: REQ-408 row covers oneo-vehicled DrivingLocked and lockout-source-lost = locked. Add with T-008 decision (a): SEC-2 negative case oneo-phone writing non-phone.* keys -> NotAllowed.
