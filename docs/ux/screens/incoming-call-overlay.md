# Screen: Incoming call overlay

Journey: J-08 step 1 · Parent: overlay on any screen · Moving: allowed; Answer/Reject never locked

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Scrim | 0,56,1280,584 | color.bg at 60% opacity | Does not cover status or nav bar |
| Card | 50,96,1180,320 | color.surface, rounded 16 | Non-modal in effect; screen beneath stays visible |
| Caller name | 90,128,1100,56 | Name (text.title) | - |
| Number | 90,184,1100,40 | Number (text.secondary) | - |
| Reject | 90,300,500,96 | ic_call_reject, "Reject" (color.danger) | Primary size |
| Answer | 690,300,500,96 | ic_call_answer, "Answer" (accent) | Primary size |
| Status bar | 0,0,1280,56 | Global | Still visible |
| Nav bar | 0,640,1280,80 | Global | Still visible |

## States
| State | Treatment |
|---|---|
| Ringing, name known | Name + number |
| Unknown number | "Unknown caller" + number |
| Private number | "Private number" |
| Media active | Media ducks or pauses (per J-08); overlay on top |
| Answered | Overlay closes; In-call screen opens |
| Rejected or missed | Overlay dismissed; no screen change |
| Caller ends | Overlay dismissed automatically |
