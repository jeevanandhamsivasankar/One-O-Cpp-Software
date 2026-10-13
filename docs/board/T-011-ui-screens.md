# T-011: Screen specifications and visual system

- Owner: ui-designer
- Phase: Design
- Reviewer: ux-lead
- Read: docs/ux/journeys.md, docs/ux/guidelines.md, this ticket
- Change: docs/ux/screens/, assets/, this ticket's Log

## Goal
Specify MVP screens and the visual design system.

## Acceptance criteria
- [ ] docs/ux/screens/design-system.md: colours (day/night), typography, spacing, icon list.
- [ ] One spec file per MVP screen (layout, components, states) under docs/ux/screens/.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
- Status: done - design-system.md + 14 screen specs in docs/ux/screens/ (colours day/night, type, spacing, icon names; no binary assets). Colour/font values are ASSUMPTION for ux-lead confirmation.
- Status: done - phone-dialer.md keypad fixed to 88x76 keys, 16 gap; grid 296x352 now ends y 616, above nav bar (y 640).
- Review: changes needed (minor) - tech-lead - all component boxes checked inside 1280x720 / content y 56-640 and match guidelines grid, targets and lockout rules. Fix: phone-dialer.md keypad "3x4 keys, 88x88, 16 gap" needs 296x400 but box is 296x352 (would end at y 664, over nav bar) - use 88x76 keys with 16 gap (fits 296x352) or adjust box; paired-devices.md "confirm with ux-lead" still open (ux-lead is reviewer).
Review: ux-lead - paired-devices lock while moving = YES (add/remove/forget locked; connect/switch to paired device allowed); note updated in paired-devices.md.
- Review: approved - tech-lead - re-check: dialer keypad 88x76, 16 gap, ends y 616; paired-devices lock decision (add/remove/forget locked, connect allowed) recorded. Note for T-008: RemoveDevice must return DrivingLocked service-side.
