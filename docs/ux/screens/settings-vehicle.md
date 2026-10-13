# Screen: Settings > Vehicle

Journey: J-03 · Parent: Settings · Moving: values readable; editing locked

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,1180,56 | "Vehicle" (text.title) + ic_back | Back returns to Settings |
| Row Lighting | 50,160,1180,88 | ic_light, "Lighting mode", current value, ic_chevron_right | Opens option list |
| Row Units | 50,248,1180,88 | ic_units, "Units", "km/h" or "mph" | Metric/imperial independent of language |
| Row Climate | 50,336,1180,88 | ic_climate, "Climate display", "On" / "Off" | - |
| Option list | 50,160 + n*88, 1180,88 each | Max 4 options, radio marker ic_check | Shown after row tap |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Default | Current values from VehicleSignals |
| Applying | Selected row shows "Applying" + spinner; row inactive; other rows still readable |
| Confirmed | Row shows vehicle-confirmed value; ic_check |
| Failed | Row reverts to actual value; toast "Setting not applied" + ic_retry (REQ-028) |
| Value unavailable | "--" |
| Moving | Rows readable; tap shows lock + "Available when parked"; option list not opened |
