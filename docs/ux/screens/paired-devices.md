# Screen: Paired devices

Journey: J-07, J-05 · Parent: Phone > Paired devices · Moving: list readable; actions locked (DECIDED by ux-lead: YES, lock add/remove/forget while moving; connect/switch to an already paired device stays allowed. Rationale: remove/pair are settings edits per REQ-048 and D-08; banner per guidelines.md)

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,820,56 | "Paired devices (3 of 5)" (text.title) | Count of max 5 |
| Row 1..5 | 50,160 + n*88, 1180,88 | ic_bt, device name, "Connected" / "Not connected" | Max 5 rows, no scroll needed |
| Row action | right side of row, 76x76 | ic_delete (remove), connect toggle | Locked when moving |
| Add button | 890,80,340,76 | ic_add "Pair new phone" | Top-right, beside title. Locked when moving. Replaced by text at 5 devices |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Default | Rows with state text; connected row shows ic_check |
| Empty | "No paired devices" + Pair new phone button (parked only) |
| Remove | Confirm dialog "Remove <name>?" with Cancel / Remove (primary) |
| Connecting | "Connecting" spinner on row, row inactive |
| Moving | Actions show ic_lock; tap shows "Available when parked" |
