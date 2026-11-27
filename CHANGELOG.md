# Changelog

All notable changes to this project are in this file.

The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).
The project does not have version numbers yet. Entries use dates.

## [Unreleased]

### Added

- Zephyr RTOS firmware skeleton in C in `firmware/`.
  Board target: `esp32s3_devkitc/esp32s3/procpu`.
- Fixed-rate control loop at 200 Hz with an absolute deadline.
- Loop statistics: period, late time, overrun count, and a summary once each second.
- `Makefile` in `firmware/` with targets `build`, `pristine`, `flash`,
  `monitor`, `run`, `menuconfig`, and `clean`.
- `west.yml` that pins Zephyr v4.5.0 and only `hal_espressif`.
- CI workflow `.github/workflows/build.yml`. It builds `firmware/` on each push
  and pull request, and uploads `zephyr.bin` and `zephyr.elf`.
- `PROGRESS.md` with the plan and the current state.

### Changed

- Firmware moves from Rust (esp-hal) to Zephyr in C.
  Reason: get experience with Zephyr.

### Removed

- Rust firmware (esp-hal). It is only in the git history.

## 2026-11-25

- Initial commit.
