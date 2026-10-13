# One-O Design System (MVP)

Canvas 1280x720, 1 dp = 1 px. Rules from `docs/ux/guidelines.md`. ASSUMPTION: font, colour values and icon set to be confirmed by ux-lead.

## Colour tokens
| Token | Day | Night | Use |
|---|---|---|---|
| color.bg | #F4F5F7 | #15181C | Screen background |
| color.surface | #FFFFFF | #1F232A | Tiles, list rows, cards |
| color.divider | #D5D9DF | #323842 | List row dividers |
| color.text.primary | #1A1C1F | #E8EAED | Titles, values (>= 4.5:1) |
| color.text.secondary | #4A4F57 | #B5BBC4 | Secondary text (>= 4.5:1) |
| color.accent | #0060C0 | #6CB4FF | Active source, focus, primary button (>= 4.5:1 text on bg) |
| color.accent.on | #FFFFFF | #0B1220 | Text/icon on accent fill |
| color.danger | #B3261E | #FF8A80 | End call, reject, error (>= 4.5:1) |
| color.disabled | #9AA0A8 | #4A505A | Locked controls (always with lock icon) |
| color.toast.bg | #2B2F36 | #E8EAED | Toast / banner fill |
| color.toast.text | #FFFFFF | #15181C | Toast / banner text |

Rules: state is never shown by colour alone (add text or icon). Icons >= 3:1 on their background. Theme switch: crossfade <= 300 ms, no layout shift.

## Typography
Font: Noto Sans (Regular, SemiBold) - covers de-DE and en-US. Line height 1.25x size. Layout must tolerate +35% string length (German).

| Token | Size | Weight | Use |
|---|---|---|---|
| text.readout | 48 px | SemiBold | Speed, gear, clock in call |
| text.title | 36 px | SemiBold | Screen titles, caller name, now-playing title |
| text.body | 28 px | Regular | List row labels, body |
| text.secondary | 24 px | Regular | Sub-labels, status text, timestamps |

Long text: single line, ellipsis. No auto-scroll or animated text while moving.

## Spacing and layout
- Spacing scale: space.1 8, space.2 16, space.3 24, space.4 32 px.
- Status bar y 0-56. Content y 56-640 (1280x584). Nav bar y 640-720.
- Content grid: x 50-1230 (12 columns of 80 px, 20 px gutter). Vertical content inset 24 px: y 80-616.
- Nav bar: 5 equal items, 256x80 px each (Home, Back, Media, Phone, Settings), always visible.

## Touch targets
| Type | Min size | Min gap |
|---|---|---|
| Any tappable | 76x76 | 16 px |
| Primary (answer, play, end call, Home) | 96x96 | 24 px |
| List row | 1232x88 (full width) | 0 (divider) |
| Slider | thumb 64, hit area 96 tall | - |
| Home tile | 380x240 | 20 px |

## Components
| Component | Spec | Behaviour |
|---|---|---|
| Status bar | 1280x56, surface colour | Time left; BT, phone signal, alert icons right. Updates <= 1 s |
| Nav bar | 1280x80 | Home, Back, Media, Phone, Settings. Never locked. Disabled state never used |
| Locked control | Grey (color.disabled) + ic_lock at top-right | Tap shows toast "Available when parked" (>= 3 s). No action |
| Lockout banner | 1232x72 at y 80, toast colours | Non-modal, auto-dismiss >= 3 s, never covers nav bar. Shown when speed > 8 km/h or unavailable |
| Toast | 1232x72 at y 552-616 | Errors and notices; auto-dismiss >= 5 s; retry button 76x76 when relevant |
| Primary button | min 240x96, accent fill | Pressed visual <= 100 ms |
| Secondary button | min 240x76, outline in color.accent | - |
| Segmented control | 76 tall, equal segments | Used for Auto/Day/Night and Dialer/Recents |
| Slider | track 8 px, thumb 64 px | Immediate apply |
| Progress bar | 8 px tall, accent | Indexing and call duration |
| Spinner | 48 px | "Applying" and "Searching" states |

## Icons (names only; assets not created)
Monochrome outline, 48 px glyph inside 76 px target, colour from tokens above.

| Name | Meaning |
|---|---|
| ic_home | Nav: Home |
| ic_back | Nav: Back |
| ic_media | Nav/tile: Media |
| ic_phone | Nav/tile: Phone |
| ic_settings | Nav/tile: Settings |
| ic_bt | Bluetooth state |
| ic_signal | Phone signal |
| ic_usb | USB source |
| ic_alert_door | Door-open warning |
| ic_alert_lamp | Lamp warning |
| ic_lock | Locked while driving |
| ic_warning | Error / unavailable |
| ic_retry | Retry action |
| ic_check | Active / confirmed |
| ic_chevron_right | Row leads to sub-screen |
| ic_play | Play |
| ic_pause | Pause |
| ic_next | Next track |
| ic_prev | Previous track |
| ic_volume | Volume |
| ic_mute | Muted |
| ic_folder | USB folder |
| ic_artist | USB artist |
| ic_album | USB album |
| ic_track | USB track |
| ic_dialpad | Dialer keypad |
| ic_recents | Call recents |
| ic_call_answer | Answer call |
| ic_call_end | End call |
| ic_call_reject | Reject call |
| ic_pair | Pair new phone |
| ic_delete | Remove paired device |
| ic_light | Lighting mode |
| ic_units | Units |
| ic_climate | Climate display |
| ic_display | Display settings |
| ic_driving | Driving lockout settings |
| ic_theme_auto | Theme: Auto |
| ic_sun | Theme: Day |
| ic_moon | Theme: Night |
| ic_add | Add item |
| ic_minus | Decrease value |
