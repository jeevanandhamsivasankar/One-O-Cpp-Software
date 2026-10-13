# ADR-005: Secure boot, read-only rootfs and A/B update layout

- Status: Accepted (pending D-05, D-11 confirmation)
- REQ: REQ-052, 053, 109, 208, 403, 404

## Decision
| Item | Choice |
|---|---|
| Chain of trust | i.MX HAB verifies SPL/U-Boot; U-Boot verifies signed FIT (kernel, DTB, initramfs, dm-verity root hash) (REQ-052) |
| Rootfs | read-only ext4 with dm-verity, root hash inside signed FIT (REQ-053) |
| Writable data | separate `/data` ext4 (journalled) for settings, logs, BT bonds, media index (REQ-109) |
| Slots | A/B pairs (fit_x + rootfs_x), updated together; the FIT lives on its own raw partition (fit_a/fit_b), not in the verity rootfs, because U-Boot reads it before verity is set up; U-Boot boot-count with fallback to previous slot |
| Update tool | RAUC with signed bundles (X.509), slot status = version metadata (REQ-208); R1 install via USB/service only, no OTA client |
| Keys | Signing keys in OEM release process / HSM; dev keys only in dev images (REQ-403) |
| No-HAB fallback | If SoC fuses/HAB unavailable: RAUC verifies bundle signature at install; gap recorded as risk by security-engineer (REQ-404) |

## Alternatives
| Option | Rejected because |
|---|---|
| SWUpdate | Viable; RAUC chosen for simpler A/B + verity bundle integration with Yocto (meta-rauc) |
| Mender | Brings OTA client/server, out of R1 scope |
| Single rootfs, rw | No rollback, no integrity, power-loss risk |

## Consequences
- eMMC 8 GB: U-Boot in boot0/boot1, fit_a/fit_b 2x 32 MB, rootfs_a/rootfs_b 2x 2 GB (verity hash ~32 MB inside each slot, so rootfs content <= ~1.9 GB), /data ~3.1-3.2 GiB (estimate, verify on board: ~7.2-7.3 GiB usable minus 2x 2 GiB slots) (docs/platform/yocto.md section 4).
- Developer images need a verity-disabled variant; production image must be built with verity + HAB-closed check.
