# Screen: Settings > Display

Journey: Settings > Display (US-007, D-04) · Parent: Settings · Moving: values readable; editing locked

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,1180,56 | "Display" (text.title) + ic_back | - |
| Theme label | 50,152,1180,40 | "Theme" (text.secondary) | - |
| Theme control | 50,200,1180,76 | Segmented: ic_theme_auto "Auto" / ic_sun "Day" / ic_moon "Night" | Auto default |
| Language label | 50,300,1180,40 | "Language" (text.secondary) | - |
| Language rows | 50,348,1180,88 each | "English (US)" / "Deutsch" with ic_check on active | Runtime switch, no restart |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Auto | Follows headlight/ambient signal; if unavailable, Night 19:00-07:00 |
| Day / Night | Manual override; crossfade <= 300 ms, no layout shift |
| Language switch | All strings update; layout must fit +35% German text |
| Moving | Controls locked with ic_lock; tap shows "Available when parked" |
