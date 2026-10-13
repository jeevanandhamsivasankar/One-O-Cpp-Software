# Screen: Source switch

Journey: J-04 step 1, J-05 step 1, J-06 step 3 · Parent: Now Playing (source label) · Moving: allowed (2 rows, no text entry)

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Title | 50,80,1180,56 | "Source" (text.title) | - |
| Row USB | 50,160,1180,88 | ic_usb, "USB", state text, ic_check if active | Full-width row |
| Divider | 50,248,1180,1 | color.divider | - |
| Row Bluetooth | 50,256,1180,88 | ic_bt, "Bluetooth", "Connected: <phone name>" or "Not connected" | Full-width row |
| Nav bar | 0,640,1280,80 | Global | - |

## States
| State | Treatment |
|---|---|
| Default | Active source has ic_check and text "Active" |
| USB no device | Row subtext "Insert USB"; row inactive |
| BT no phone | Row subtext "Not connected"; action row "Connect phone" (ic_pair) to Phone; disabled with ic_lock when moving |
| Switching | Target row shows "Applying" spinner; previous source paused |
| Switch failed | Toast "Source not available" + ic_retry |
