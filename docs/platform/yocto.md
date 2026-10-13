# Yocto platform design (R1)

Inputs: ADR-001 (platform), ADR-005 (boot/update), system.md. Status: design only, never built (no Linux host); all values are targets to verify on first image build.

## 1. Release and layer stack
| Layer | Source | Purpose |
|---|---|---|
| poky (openembedded-core, bitbake, yocto-docs) | Yocto 5.0 Scarthgap LTS | base, GCC 13 |
| meta-openembedded (oe, networking, multimedia) | scarthgap | BlueZ/oFono/PipeWire deps |
| meta-freescale, meta-freescale-distro | scarthgap | NXP i.MX8M BSP (linux-imx, imx-boot, CAAM/HAB tooling) |
| meta-qt6 | 6.8 branch | Qt 6.8 LTS |
| meta-rauc | scarthgap | RAUC + bundle class |
| **meta-oneo** | this repo, `yocto/meta-oneo` | distro, image, app/service recipes, wks, RAUC config |

Priority: meta-oneo=9 (above BSP) so bbappends win. Machine: `imx8mm-oneo` (placeholder; derive from the customer board DTS once D-07 SoC is confirmed; default base `imx8mm-lpddr4-evk`). Machine config lives in a BSP bbappend/machine file, not in the distro.

## 2. Distro `oneo` (conf/distro/oneo.conf)
Based on poky; systemd init, usrmerge; features: opengl, bluetooth, usbhost, pipewire, alsa, ipv4, pam. No x11/wayland (EGLFS/KMS), no sysvinit. Read-only verity rootfs; writable state only on `/data`. SPDX generation and rm_work enabled. Signing keys are variables supplied by the OEM release process (REQ-403), empty in repo.

## 3. Images
| Image | Contents | Notes |
|---|---|---|
| `oneo-image` (production) | systemd, dbus-broker, PipeWire+WirePlumber, BlueZ5, oFono, obexd, Qt 6.8 runtime (QtQuick, Controls, DBus, EGLFS), oneo-hmi/vehicled/mediad/phoned/system, RAUC, minimal userland (no can-utils) | ro rootfs, verity, no getty/ssh/package manager, HAB-closed check in build |
| `oneo-image-dev` | production + ssh, gdbserver, strace, perf, can-utils, verity disabled (`ONEO_VERITY=0`), dev keys | dev only; never released |
| `oneo-bundle` | RAUC bundle of oneo-image rootfs+FIT | signed X.509 |
| SDK | `bitbake oneo-image -c populate_sdk` | cross toolchain + Qt 6.8 + sysroot; CMake toolchain file used by the same CMake as host mocks |

Recipes to create (owners yocto-build-engineer/kernel-engineer): `oneo-*` app recipes (CMake, systemd units per ADR-004), `linux-imx` bbappend (trimmed config, built-in boot drivers, dm-verity), `u-boot-imx` bbappend (splash, bootdelay=0, FIT verify, boot-count), `rauc-conf`, `oneo-initramfs`, `oneo-image.bb`, `oneo-bundle.bb`, `oneo-oneo.wks.in`.

## 4. Partition layout (answers T-005 Request) - 8 GB eMMC
SPL+U-Boot (`imx-boot` flash.bin) in eMMC hardware boot0, redundant copy in boot1 (i.MX8M reads at 33 KB offset); user area GPT:

| # | Name | Size | FS | Mode | Content |
|---|---|---|---|---|---|
| raw | env_a/env_b | 2x 128 KB | raw | rw | redundant U-Boot env (boot-count, slot) |
| 1 | fit_a | 32 MB | raw | ro | signed FIT slot A (RAUC raw slot) |
| 2 | fit_b | 32 MB | raw | ro | signed FIT slot B (RAUC raw slot) |
| 3 | rootfs_a | 2 GB | ext4 + verity hash appended | ro | rootfs slot A |
| 4 | rootfs_b | 2 GB | ext4 + verity hash appended | ro | rootfs slot B |
| 5 | data | remainder (~3.1-3.2 GiB; estimate, verify on board) | ext4 journalled | rw | settings, logs, BT bonds, media index |

Confirmed vs ADR-005 / system.md section 5, with two refinements: (a) the 64 MB "boot" area is split into fit_a/fit_b so the FIT is updated per slot with its own rootfs (a FIT inside a verity device cannot be read before verity is set up); (b) the verity hash tree (~1.6% = ~32 MB) lives inside the 2 GB slot, so rootfs content must be <= ~1.9 GB. Rootfs also holds `rootfs-version` for RAUC slot metadata. `/data` is mounted `noexec,nosuid,nodev`; fsck on boot, size-capped logs.

## 5. Secure boot chain (HAB / FIT)
1. BootROM HAB verifies `imx-boot` (SPL + ATF + U-Boot) with SRK table (fused SRK hash, CSF signed) - REQ-052.
2. U-Boot (control DTB holds the FIT public key, `CONFIG_FIT_SIGNATURE`, `CONFIG_FIT_ENABLE_RSASSA_PSS` optional) loads the FIT of the active slot: kernel, DTB, initramfs, plus `verity` root hash in a signed property/in the kernel cmdline config node; rejects on bad signature.
3. Env: `bootslot`, `bootcount`, `bootlimit=3`; `altbootcmd` flips slot. RAUC marks good after `oneo-system` reports healthy (ADR-005, REQ-208).
4. Initramfs runs `veritysetup` with the signed root hash on rootfs_x, mounts ro, mounts `/data`, switch_root. Production debug lock (REQ-410): U-Boot built with `bootargs` locked (no env override, console off, no JTAG/serial shell) once HAB is closed. USB class allow-list (REQ-409): the external USB port is Mass Storage class only; any on-board USB device is allowed by port path plus VID:PID, never by class. Everything else is denied in the production image.
5. Keys: HAB SRKs and FIT/RAUC keys are OEM HSM keys; dev builds use throw-away dev keys flagged in the image (`/etc/oneo-devkeys`). No-HAB fallback (D-11): step 1 absent, steps 2-4 still run in software trust only if U-Boot itself is not replaced - recorded as risk by security-engineer (REQ-404). CI check: production build fails if `ONEO_VERITY=0` or dev keys detected.

## 6. Boot-time budget feasibility (REQ-100, 7.5 s target vs 10 s)
| Stage | Budget | Feasible? | Actions |
|---|---|---|---|
| ROM+SPL+U-Boot+splash 1.5 s | yes, with risk | bootdelay=0, no USB/net probing, FIT verify with CAAM-accelerated SHA/RSA (~0.2-0.3 s for ~25 MB FIT; keep initramfs small, LZ4/uncompressed). Risk: splash in U-Boot needs a U-Boot display driver (LCDIF/DSI) for the final panel; fallback is early kernel splash (+0.5 s, still < 3 s requirement) |
| Kernel+initramfs+verity 3.0 s | yes | `quiet`, built-in MMC/DRM/verity, no modules in boot path, async probes, verity lazy hashing (no full-device scan) |
| systemd to dbus+/data 4.0 s | yes | minimal units, no networkd-wait/getty, journald volatile + flush to /data late |
| Services ready 5.0 s / HMI frame 6.5 s | yes, tight | oneo-hmi `After=dbus.socket` only; shader cache pre-populated in image; tune with `systemd-analyze` + bootchart per build |
| Interactive 7.5 s | margin 2.5 s | Measure on real HW first; if Cortex-A53 ROM+eMMC read is slow, tradeoff is FIT size. Warm resume <= 3 s (REQ-101) is a kernel/suspend item for kernel-engineer. |

Verdict: feasible on i.MX8M-class by design, unproven until measured; first measurement gate on the first bootable image.

## 7. Build flow
`kas`-style manifest (`yocto/kas-oneo.yml`, to be added by yocto-build-engineer) pins all layer revisions; `kas build` -> `oneo-image` (wic.zst + ext4), `oneo-bundle`, SDK. sstate/downloads cache shared in CI; signing step is a separate release job holding keys. Host app builds (mocks) use the same CMake outside Yocto (CLAUDE.md).

## 8. Open points
D-07 SoC/board and RAM unconfirmed (machine name placeholder); D-11 HAB fuse availability; U-Boot splash driver availability; GPL/LGPL review of Qt and kernel by release-manager.
