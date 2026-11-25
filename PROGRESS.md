# Progress

## Plan

- [x] 0. Build and flash the firmware skeleton ("Hello world!" on the serial
      monitor).
- [ ] 1. Read the angle from the IMU (GY-521 / MPU-6050). Use a complementary
      filter.
- [x] 2. Run a fixed-rate control loop, about 200 Hz. (needs language choice)
- [ ] 3. Write and tune a PID controller on the device. (simulation done, see
      below)
- [ ] 4. Log angle, angular speed and motor command. (needs hardware)
- [ ] 5. Train a small neural network on the PC to copy the PID output.
      (simulation done, see below)
- [ ] 6. Convert the weights to int8. (done in simulation; run on ESP32-S3 still
      open)

## Current state

- 2026-11-25: Move the firmware from Rust (esp-hal) to Zephyr in C. Reason:
  get experience with Zephyr. New skeleton in `firmware/` (200 Hz loop
  with absolute deadline, period and late statistics, overrun count, summary
  once each second). The skeleton builds without errors or warnings.
  Tested on the board: ticks=200, period 5000 us, late_max=0 us, overruns=0.
- `firmware/` is outside the Zephyr workspace. `west flash` and
  `west espressif monitor` need `ZEPHYR_BASE=~/zephyrproject/zephyr`
  (fish: `set -Ux ZEPHYR_BASE ~/zephyrproject/zephyr`).
- Zephyr install: workspace `~/zephyrproject` (Zephyr v4.5.0, same as `west.yml`),
  Python 3.12 venv in `~/zephyrproject/.venv` (fish:
  `source ~/zephyrproject/.venv/bin/activate.fish`). SDK with only the
  `xtensa-espressif_esp32s3_zephyr-elf` toolchain. Espressif blobs fetched.
- Build: `make` in `firmware/` (targets: build, pristine, flash,
  monitor, run, menuconfig, clean). The Makefile sets `ZEPHYR_BASE` and the
  venv `PATH` itself, so no venv activation is necessary.
- Flash speed: the Makefile passes the `/dev/cu.usbmodem*` port to west.
  Without a port, the Zephyr runner probes all serial ports (~9 s).
  `--esp-skip-flashed` skips the write if the image did not change.
- CI: `.github/workflows/build.yml` builds `firmware/` on each push and pull
  request and uploads `zephyr.bin` and `zephyr.elf`. `west.yml` pins Zephyr
  v4.5.0 and only `hal_espressif`. CI passes on GitHub (branch
  `zephyr-migration`, about 2.5 min). It fetches only the 9 ESP32-S3 blobs
  with retry (the blob server sometimes returns HTTP 504).
- 2026-11-25: Add `CHANGELOG.md` (Keep a Changelog format, entries by date).
- Note: the board file uses 8 MB flash. The N16R8 board has 16 MB. This is
  sufficient for now.

Rust firmware (old, only in git history, commit 1c72059):

- Toolchain: standard espup install in `~/.rustup` (toolchain "esp"). fish
  sources `~/export-esp.sh`.
- Debug: VS Code with probe-rs over the built-in USB-JTAG. Config in
  `.vscode/launch.json` and `.vscode/tasks.json` (not in git).

## Done on PC (folder `sim/`)

## Open questions

## Next step

Step 2: fixed-rate loop at 200 Hz (no IMU needed).

- [x] Use an absolute deadline: next = next + 5 ms.
- [x] Measure tick time: keep the maximum, count overruns.
- [ ] Print a summary once each second, not on each tick.
- [ ] Optional: toggle a GPIO pin and measure the period.
