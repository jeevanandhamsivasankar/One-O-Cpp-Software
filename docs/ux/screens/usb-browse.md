# Screen: USB browse

Journey: J-04 steps 1-3 · Parent: Now Playing or Source switch (USB) · Moving: locked to top-level shortcuts, Now Playing, last-played (max 5 rows, no scroll)

## Layout
| Region | Box (x,y,w,h) | Content | Notes |
|---|---|---|---|
| Status bar | 0,0,1280,56 | Global | - |
| Header | 50,80,1180,56 | Breadcrumb (text.title), e.g. "USB > Music" | Tap segment goes up |
| Indexing bar | 50,140,1180,40 | Progress bar + "Indexing 42%" (text.secondary) | Only while indexing |
| Shortcuts | 50,96,1180,88 | Now Playing, Last played (rows) | Visible when moving |
| List | 50,192,1180,424 | Rows 88 tall, 4 visible when indexing bar shown, 5 without | Scrolls when parked only |
| Nav bar | 0,640,1280,80 | Global | - |

Row types: ic_folder / ic_artist / ic_album / ic_track + label + ic_chevron_right for containers.

## States
| State | Treatment |
|---|---|
| Indexing | Progress bar with percentage; list shows already-indexed items |
| Empty | "No supported audio files" (text.body) centred |
| Unsupported file | Skipped; toast "1 file skipped" (>= 5 s) |
| Moving | Only shortcuts and up to 5 rows shown; no scroll; long lists replaced by "Available when parked" banner |
| Parked | Full list, scroll; > 5 rows scroll |
| USB removed | Playback paused; toast "USB removed"; return to Source switch |
| Track selected | Playing; navigate to Now Playing |
