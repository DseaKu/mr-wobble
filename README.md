# mr-wobble

A one-axis balancing device (inverted pendulum).
A small neural network controls the motor.
Training runs on the PC. Inference runs on the device.

## Hardware

- ESP32-S3-N16R8 board (16 MB flash, 8 MB PSRAM)
- IMU for the angle (MPU-6050)
- DC motor with encoder and motor driver

## Status

Work in progress. The firmware skeleton runs a fixed 200 Hz control loop.
The IMU, the PID controller, and the neural network are not on the device yet.
See [PROGRESS.md](PROGRESS.md) for the plan and the current state.

## Firmware

The firmware uses Zephyr RTOS (v4.5.0) in C. It is in `firmware/`.
Board target: `esp32s3_devkitc/esp32s3/procpu`.

Requirements:

- Zephyr workspace in `~/zephyrproject` with a Python venv in `.venv`
- Zephyr SDK with the `xtensa-espressif_esp32s3_zephyr-elf` toolchain
- Espressif blobs (`west blobs fetch hal_espressif`)

Build and flash:

```sh
cd firmware
make          # build
make flash    # build and flash
make monitor  # serial monitor (exit with Ctrl+])
make run      # build, flash, and open the monitor
```

The Makefile finds the first `/dev/cu.usbmodem*` port.
To use a different port, set `PORT`:

```sh
make flash PORT=/dev/cu.usbmodemXXXX
```

## CI

GitHub Actions builds the firmware on each push and pull request.
The workflow is in `.github/workflows/build.yml`.

## License

No license yet.
