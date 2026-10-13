# Screen: Splash

Journey: J-01 step 1 · Parent: boot · Moving: n/a (shown at ignition on)

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Full screen | 0,0,1280,720 | color.bg | No status or nav bar |
| Logo | 490,280,300,160 | Brand logo (asset name: img_brand_logo) | Centred |
| Progress | 490,480,300,8 | Indeterminate progress bar, accent | Hidden after 1 s if still loading |

## States
| State | Treatment |
|---|---|
| Boot | Logo + progress bar. Max 3 s, then Home |
| Service slow | Progress bar continues; Home opens when Home is ready (cold start <= 10 s) |
| Crash recovery | Same as boot, then Home (J-01 error rule) |
| Theme | Day or Night per current theme (fallback: time of day) |
