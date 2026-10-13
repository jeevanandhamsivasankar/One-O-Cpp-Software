# T-009: Yocto layer and platform design

- Owner: yocto-bsp-lead
- Phase: Design
- Reviewer: tech-lead
- Read: docs/architecture/system.md, docs/product/decisions.md, this ticket
- Change: docs/platform/yocto.md, yocto/meta-oneo/conf/, this ticket's Log

## Goal
Design the Yocto platform: release, BSP layer, custom distro and image, layer structure, SDK and update hooks.

## Acceptance criteria
- [ ] yocto.md: Yocto release, layer stack (poky, BSP, meta-qt6, meta-oneo), machine, distro features, image contents, build/SDK flow.
- [ ] yocto/meta-oneo/conf/layer.conf and conf/distro/oneo.conf skeletons.

## Log
<!-- Owners append one line each: Status / Request / Blocked / Review -->
- Status: done - yocto-bsp-lead - docs/platform/yocto.md (layers, distro, images, partitions, HAB/FIT chain, boot budget feasible-but-unmeasured, build/SDK) + meta-oneo conf/layer.conf, conf/distro/oneo.conf. T-005 Request answered (FIT moved to per-slot fit_a/fit_b partitions; verity hash inside 2 GB slot).
- Request: yocto-build-engineer - add kas manifest, oneo-image/bundle recipes, wks, machine file once D-07 board is confirmed.
- Request: kernel-engineer - linux-imx trim/verity config, U-Boot splash + FIT verify + boot-count per yocto.md sections 5-6.
- Review: changes needed (minor) - tech-lead - layer stack, distro, images, A/B layout and boot budget consistent with system.md/ADR-005. Fix: (1) section 4 fit_a/fit_b FS "FAT/raw" -> "raw" (ADR-005 says raw partition; RAUC slot type=raw); (2) remove stale refinement text "system.md puts the FIT in rootfs_x" (resolved in T-005); (3) data size: 8 GB eMMC user area ~7.2-7.3 GiB => remainder ~3.1-3.2 GiB, not ~3.8 GB - state as estimate to verify; (4) section 5 step 4 / section 3: cite REQ-410 for the production debug lock (console off, no getty/ssh, USB gadget off) and REQ-409 for the udev USB class allow-list; (5) nit: "can-utils-free minimal userland" -> "minimal userland (no can-utils)".
- Status: done - yocto-bsp-lead - applied tech-lead review: fit_a/fit_b raw, stale system.md note removed, /data ~3.1-3.2 GiB estimate, REQ-410/REQ-409 cited, userland wording fixed.
- Review: changes needed (one line) - tech-lead - fit raw, stale note, /data size, userland wording, REQ-410 OK. Fix: section 5 step 4 REQ-409 sentence says udev permits "mass-storage and required BT/HID classes" - contradicts REQ-409 / threat T-08 (MSC only; HID rejected). BT is on UART (system.md) and touch is not a USB class device; change to "external USB port: Mass Storage class only; any on-board USB device is allowed by fixed port path + VID:PID, never by class".
- Status: done - yocto-bsp-lead - yocto.md s5 step 4: REQ-409 wording fixed (external USB Mass Storage only; on-board devices by port path + VID:PID, never by class).
- Review: approved - tech-lead - re-check: REQ-409 wording now external port Mass Storage only, on-board devices by port path + VID:PID.
