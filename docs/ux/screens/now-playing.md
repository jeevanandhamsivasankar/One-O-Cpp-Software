# Screen: Now Playing

Journey: J-04 step 3, J-05 step 2, J-06 · Parent: Home > Media · Moving: fully allowed (transport, volume, source; no text entry)

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Album art | 50,96,400,400 | Cover art or placeholder (ic_album) | Square |
| Title | 490,96,740,56 | Track title (text.title), 1 line | Ellipsis |
| Artist / album | 490,160,740,80 | Artist, album (text.secondary) | 2 lines max |
| Source label | 490,250,740,40 | "USB" or "Bluetooth" + ic_usb / ic_bt | Tap opens Source switch (76 tall hit area) |
| Progress | 490,320,740,64 | Progress bar + elapsed / total (text.secondary) | Not shown for Bluetooth if unavailable |
| Transport | 490,400,740,96 | ic_prev (76), ic_play/ic_pause (96, primary), ic_next (76) | Centred, 24 px gaps |
| Volume | 490,520,740,96 | ic_volume + slider (thumb 64) | Immediate apply |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Playing | Pause icon shown; metadata live |
| Paused | Play icon shown |
| No source | Art area shows ic_usb; text "Select source" with action to Source switch |
| No metadata | Title shows file name; artist "Unknown artist" |
| BT, phone disconnected | Text "Connect phone" action to Phone (J-05); disabled with lock icon when moving |
| Source switching | Text "Applying" (text.secondary) until audible; <= 2 s |
| Long title | Ellipsis, no scrolling |
