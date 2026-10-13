# One-O HMI Guidelines

Basis: NHTSA Visual-Manual guidelines, ISO 15005/15007 principles (D-08). ASSUMPTION (confirm with customer).

## Target display (D-07, REQ-206)
10.25 in, 1280x720, 16:9, ~143 ppi => 1 px ~ 0.177 mm; 1 mm ~ 5.6 px. Design in dp = px (1:1, scale 1.0).

## Layout grid
| Item | Value |
|---|---|
| Canvas | 1280x720 landscape only |
| Status bar | top 56 px |
| Nav bar | bottom 80 px |
| Content area | 1280x584 |
| Safe margin | 24 px all sides |
| Grid | 12 columns, 80 px column, 20 px gutter (12*80 + 11*20 = 1180 + margins 2x50) |
| Spacing scale | 8, 16, 24, 32 px |
| Home tiles | 3 tiles, each 4 columns wide, >= 240 px tall |

## Touch targets
| Type | Min size | Min gap |
|---|---|---|
| Any tappable | 76x76 px (~13.5 mm) | 16 px |
| Primary (answer, play, Home) | 96x96 px (~17 mm) | 24 px |
| List row | 88 px tall, full width | 0 (divider) |
| Slider thumb | 64 px, track hit area 96 px | - |
| Edge targets | Nav bar items full height | - |

## Glance-time and task rules
| Rule | Value |
|---|---|
| Single glance | <= 2 s, no look-away >= 2 s |
| Total task time for moving-allowed tasks | <= 12 s eyes-off-road |
| Moving-allowed task depth | <= 2 taps from Home/Now Playing |
| Visible rows while moving | <= 5 |
| Touch-to-visual response | <= 100 ms (REQ-102); busy indicator if work > 300 ms |
| No auto-scrolling/animated text while moving; no video |
| Alerts | Non-modal except incoming call; auto-dismiss >= 5 s, never cover nav bar |

## Typography and contrast
| Item | Value |
|---|---|
| Body | >= 28 px (~5 mm) |
| Secondary | >= 24 px |
| Title | 36 px |
| Speed/gear readout | 48 px |
| Font | sans-serif with de-DE and en-US glyphs; allow 35% string expansion for German |
| Contrast | >= 4.5:1 text, 3:1 icons; state never by colour alone |

## Driving lockouts (REQ-048..050)
| Item | Rule |
|---|---|
| Trigger | speed > 8 km/h (5 mph), configurable; speed unavailable => locked |
| Hysteresis | Lock at > threshold; unlock after speed <= threshold for 1 s |
| Locked | text entry, long list browsing, pairing, settings editing |
| Never locked | Home/Back, call answer/reject/end, volume, transport, source |
| Indication | Lock icon + grey control; tap shows "Available when parked" banner (>= 3 s) |
| Mid-flow | Keyboard/pairing dialogs close on lock, state discarded, user told |
| Service rejection (REQ-408) | If a service rejects a pairing/settings-edit command because it is locked (HMI state stale or lagging), the control reverts to the actual state and shows the same "Available when parked" banner; no error toast, no retry action |
| Source of truth | VehicleSignals only; UI does not read CAN (US-009) |

## Theme (day/night) (REQ-015, US-007)
| Item | Day | Night |
|---|---|---|
| Background | light neutral | dark neutral (not pure black) |
| Switch trigger | headlight/ambient signal (D-06) | same |
| Manual override | Auto / Day / Night in Settings > Display | |
| Transition | crossfade <= 300 ms, no layout shift | |
| Fallback | signal unavailable => follow time of day, Night 19:00-07:00 | |
| Contrast | rules above hold in both themes | |

## Feedback and states
| State | Treatment |
|---|---|
| Pressed | visual change <= 100 ms |
| Disabled/locked | grey + lock icon |
| Unavailable data | "--" |
| Pending vehicle command | "Applying" spinner, control inactive |
| Failure | toast + retry, revert to actual state |
| Haptics/sound | optional chime only; no haptics in MVP |

## Localisation
en-US, de-DE runtime switch, metric/imperial independent of language (D-04, REQ-017/018). Mirror layout not required.
