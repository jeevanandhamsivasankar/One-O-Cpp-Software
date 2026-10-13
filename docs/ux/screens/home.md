# Screen: Home

Journey: J-01, J-02 · Parent: boot, all screens via Home · Moving: allowed (read-only status, tiles)

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global status bar | See design-system |
| Tile Media | 50,96,380,240 | ic_media + "Media" (text.title) + source name (text.secondary) | Opens Now Playing |
| Tile Phone | 450,96,380,240 | ic_phone + "Phone" + BT state | Opens Phone |
| Tile Settings | 850,96,380,240 | ic_settings + "Settings" | Opens Settings |
| Vehicle panel | 50,360,1180,256 | Speed readout, gear readout, alert row | Read-only |
| Speed | 80,400,300,96 | Speed value (text.readout) + "km/h" | "--" if unavailable |
| Gear | 420,400,240,96 | Gear letter (text.readout) | "--" if unavailable |
| Alert row | 80,528,1120,64 | ic_alert_door, ic_alert_lamp with text | Shown only when active |
| Nav bar | 0,640,1280,80 | Global nav bar | Never locked |

## States
| State | Treatment |
|---|---|
| Default | Three tiles active, panel values live (<= 200 ms after change) |
| Signal lost | Speed and gear show "--", never last value (J-02) |
| Tile service down | Tile shows "Unavailable" + ic_retry (76x76) inside tile; tap retries |
| Door/lamp warning | Alert row shows icon + text; non-modal; auto-dismiss >= 5 s; never covers nav bar |
| Moving | Layout unchanged; no animation; tiles remain tappable |
| Night | color.bg night tokens; contrast rules hold |
