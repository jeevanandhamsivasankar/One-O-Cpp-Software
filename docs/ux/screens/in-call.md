# Screen: In-call

Journey: J-08 steps 2-3 · Parent: Incoming call overlay (answered) or Phone dialer (outgoing) · Moving: fully allowed; End, mute, volume never locked

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Caller | 50,96,1180,56 | Name (text.title) | "Unknown caller" if no name |
| Number | 50,152,1180,40 | Number (text.secondary) | - |
| Timer | 50,200,1180,80 | Elapsed mm:ss (text.readout), centred | Hidden while "Calling" |
| Mute | 50,320,380,96 | ic_mute toggle, "Mute" / "Muted" | Toggle; state by text and icon |
| Volume | 470,320,760,96 | ic_volume + slider (thumb 64) | Immediate apply |
| End call | 390,480,500,96 | ic_call_end, "End" (color.danger), primary | Never locked |
| Nav bar | 0,640,1280,80 | Global | Home and Back reachable |

## States
| State | Treatment |
|---|---|
| Calling (outgoing) | "Calling <name>" (text.body), timer hidden |
| Active | Timer running; audio routed to cabin |
| Muted | "Muted" text + ic_mute active |
| Ended | Returns to previous screen; Media resumes; overlay dismissed |
| Connection lost | Toast "Call dropped" (>= 5 s); return to previous screen |
| Moving | All controls active; no text entry |
