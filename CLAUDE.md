# Project: one-axis balancing device with a neural network

## Goal
Balance an upright object on one axis (inverted pendulum).

## Hardware
- ESP32-S3-N16R8 board (16 MB flash, 8 MB PSRAM)
- IMU sensor for the angle, for example MPU-6050
- DC motor with encoder and motor driver

## Decisions
- Firmware: Zephyr RTOS in C. Firmware lives in `firmware/`.
  Board target: `esp32s3_devkitc/esp32s3/procpu`.
- The old Rust firmware (esp-hal) is only in the git history (commit 1c72059).
- PC simulation and training: Python with NumPy in `sim/`.
- No LLM. The network is small: about 100 to 1000 weights.
- Training runs on the PC. Inference runs on the device.
- Use a complementary filter for the angle.
- Use a fixed-rate control loop, about 200 Hz.

## Rules for Claude
- Read `PROGRESS.md` at the start of each session.
- Update `PROGRESS.md` when a task is done or a decision changes.
- Do not commit unless asked.
