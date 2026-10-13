# Screen: Phone (Dialer / Recents)

Journey: J-07 entry, J-08 outgoing · Parent: Home > Phone · Moving: Recents tap-to-dial allowed (max 5 items); dialer keypad locked

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Segmented | 50,80,640,76 | "Dialer" / "Recents" | Segmented control |
| Paired state | 730,80,500,76 | BT state + "Paired devices" link | Opens Paired devices |
| Dialer display | 50,176,1180,72 | Entered number (text.title) | Dialer tab only |
| Keypad | 50,264,296,352 | 3x4 keys, 88x76 (w x h), 16 gap; grid 296x352, ends y 616 | Locked when moving |
| Call button | 386,264,96,96 | ic_call_answer (primary) | Locked when moving |
| Backspace | 386,376,96,96 | ic_back icon | Locked when moving |
| Recents list | 50,176,1180,440 | Rows 88 tall, max 5 when moving | Tap = dial |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| No phone connected | Row text "Connect phone" with ic_pair to Pair new phone; keypad still shown but disabled when moving |
| Dialer, moving | Keypad, call button, backspace grey with ic_lock; banner "Available when parked" on tap |
| Recents, moving | Max 5 rows; tap dials (Recents allowed) |
| Recents empty | "No recent calls" (text.body) |
| Syncing | "Recents syncing" (text.secondary) under list header |
| Call started | Navigate to In-call screen |
