# Defects

Owner: qa-lead. Log below the register header; one row per defect.

## Severity scale

| Sev | Meaning | Examples | Release rule | Target fix |
|---|---|---|---|---|
| 1 Critical | Safety/security breach, data loss, crash loop, boot failure, lockout bypass | REQ-048..050 failure, unsigned image boots, FS corruption | Blocks release and further test of affected area | Immediately |
| 2 High | Must feature broken or missed NFR with no workaround | Call audio missing, boot > 10 s, soak crash | Blocks release | Current iteration |
| 3 Medium | Feature degraded, workaround exists; Should feature broken | Metadata missing, theme override ignored | Release only with product-owner waiver | Next iteration |
| 4 Low | Cosmetic, minor text, non-functional polish | Misaligned icon | May ship | Backlog |

Security findings use the same scale; "high" in REQ-405 means Sev 1-2.

## Workflow

States: New -> Triaged -> Assigned -> Fixed -> Verified -> Closed. Side exits: Rejected (not a defect / cannot reproduce), Deferred (waiver), Reopened (fix failed).

| Step | Who | Action |
|---|---|---|
| Report | Anyone / test engineers | Add row with ID `DEF-nnn`, title, REQ id(s), severity proposal, repro steps, build id, logs |
| Triage | qa-lead (with tech-lead for Sev 1-2) | Confirm severity, set owner; Sev 1-2 triaged within 1 working day |
| Fix | Owning engineer | Fix with regression test; link commit; state Fixed |
| Review | tech-lead | Standard code-review gate |
| Verify | Reporting tester | Re-run failing case on new build plus related regression; Verified or Reopened |
| Close | qa-lead | Closed after verification; waivers recorded with product-owner name |

Rules: every fix adds or updates an automated test where host-testable; Sev 1 on a safety REQ requires root-cause note; open counts per severity are reported in docs/qa/results.md.

## Register

| ID | Title | REQ | Sev | State | Owner | Build | Notes |
|---|---|---|---|---|---|---|---|
| | (none yet) | | | | | | |
