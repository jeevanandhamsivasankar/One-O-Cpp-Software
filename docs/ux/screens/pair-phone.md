# Screen: Pair new phone

Journey: J-07 steps 1-3 · Parent: Phone > Pair new phone · Moving: locked (banner explains); parked only

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,1180,56 | "Pair new phone" (text.title) | - |
| Instruction | 50,144,1180,120 | "On your phone, select '<HMI name>' and confirm the code" (text.body) | HMI name from device config |
| Code | 50,280,1180,120 | 6-digit code (text.readout), centred | Shown at step 2 only |
| Timer | 50,416,1180,40 | "Cancels in 60 s" (text.secondary) | Counts down |
| Cancel | 50,496,540,96 | Secondary button "Cancel" | - |
| Confirm | 690,496,540,96 | Primary button "Confirm" | Enabled at step 2 |
| Nav bar | 0,640,1280,80 | Global | Never locked |

## States
| State | Treatment |
|---|---|
| Discoverable | Spinner (48 px) + "Waiting for phone" |
| Code shown | Code + Confirm/Cancel |
| Paired | Toast "Paired: <name>"; auto-connect; "Syncing contacts" (PBAP) |
| Max devices (5) | Prompt "Remove a device to pair another" with action to Paired devices |
| Timeout 60 s | "Pairing cancelled" + ic_retry |
| Moving | Dialog closes, state discarded, banner "Pairing cancelled: available when parked" |
| Phone rejects | "Pairing failed" + ic_retry |
