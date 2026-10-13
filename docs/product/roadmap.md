# One-O Release Roadmap

Basis: docs/product/vision.md, backlog.md, decisions.md (all defaults are `ASSUMPTION (confirm with customer)`). Dates are relative to project start (T0); to be set by delivery-manager.

## R1 - MVP (target T0 + ~6 months)
Objective: a bootable, fast, supervised IVI image with media, phone, vehicle status/settings and driving lockout, meeting all vision.md metrics.

Stories:
- E1: US-001, US-002, US-003, US-004
- E2: US-005, US-006, US-007, US-008
- E3: US-009, US-010, US-011
- E4: US-013, US-014, US-015
- E5: US-018, US-019, US-020
- E6: US-022, US-023, US-024
- E7: US-025, US-026

Exit criteria: all Must stories have passing tests; cold boot <= 10 s; 100 h soak crash-free; no open high-severity security findings; qa-lead sign-off.
Cut order if schedule slips: US-008 (second language), US-007 manual/auto theming, US-004 diagnostics view, US-020.

## R2 - Hardware options and polish (target R1 + ~3 months)
Objective: add hardware-dependent and convenience features once the platform is proven.

Stories:
- US-012 Rear camera trigger (needs camera input confirmed)
- US-016 AM/FM radio (needs tuner hardware confirmed)
- US-017 Play queue, shuffle/repeat
- US-021 SMS notifications (MAP, read-only)
- Hardening: fixes and performance tuning from R1 field feedback

Exit criteria: R1 regression suite green; camera view within 500 ms of reverse; radio presets work on tuner-equipped hardware.

## R3 - Connected platform (target R2 + ~4 months; scope needs new stories)
Objective: update and ecosystem capability.

Candidate scope (no US ids yet; product-owner to write stories):
- OTA update client and backend integration (builds on A/B design from R1)
- Navigation and maps
- Smartphone projection (CarPlay / Android Auto)
- Voice assistant, streaming services, multi-user profiles

Exit criteria: OTA update with rollback proven on target; chosen R3 features accepted by product-owner. Rear-seat displays, app store and ADAS remain out of scope until a new vision review.

## Dependencies and risks
- Customer confirmation of SoC, display, tuner/camera hardware (D-02, D-03, D-07) gates R2 scope.
- Secure boot support on the chosen SoC (D-11) may force a documented risk acceptance in R1.
- OEM-supplied DBC (D-06) needed for real CAN backend; mock backend unblocks development.
