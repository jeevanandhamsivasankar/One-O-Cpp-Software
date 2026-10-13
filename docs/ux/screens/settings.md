# Screen: Settings

Journey: J-03 step 1, J-09 step 4 · Parent: Home > Settings · Moving: navigation allowed; editing locked in sub-screens

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,1180,56 | "Settings" (text.title) | - |
| Row Vehicle | 50,160,1180,88 | ic_light, "Vehicle", ic_chevron_right | Opens Vehicle |
| Row Display | 50,248,1180,88 | ic_display, "Display", current theme value, ic_chevron_right | Opens Display |
| Row Driving | 50,336,1180,88 | ic_driving, "Driving", threshold value, ic_chevron_right | Opens Driving |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Default | Three rows, all tappable |
| Moving | Rows tappable; sub-screen editing controls locked with ic_lock |
| Parked | Same layout; editing enabled in sub-screens |
