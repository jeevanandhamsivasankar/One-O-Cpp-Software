# Screen: Settings > Driving

Journey: J-09 step 4, REQ-048..050 · Parent: Settings · Moving: threshold readable; editing locked

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,1180,56 | "Driving" (text.title) + ic_back | - |
| Label | 50,160,1180,40 | "Lockout speed threshold" (text.body) | - |
| Stepper | 50,240,1180,96 | ic_minus (96), value (text.readout) + unit, ic_add (96) | Unit follows units setting |
| Help text | 50,368,1180,80 | "Controls lock above this speed. Unlocks after 1 s at or below." (text.secondary) | - |
| Current state | 50,472,1180,88 | "Current speed: <value>" or "--" | Read-only |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Parked | Stepper active; value stored on confirm; range and step TBC by product-owner (ASSUMPTION) |
| Moving | Stepper shows ic_lock; tap shows "Available when parked"; value readable |
| Out of range | Stepper stops at limit; no toast |
