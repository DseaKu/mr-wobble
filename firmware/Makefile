# Makefile for the Zephyr firmware. It wraps the west commands.
#
#   make            build the firmware (incremental)
#   make pristine   clean build (delete build folder, then build)
#   make flash      build and flash
#   make monitor    open the serial monitor (exit with Ctrl+])
#   make run        build, flash and open the monitor
#   make menuconfig open the Kconfig menu
#   make clean      delete the build folder
#
# PORT is the first /dev/cu.usbmodem* device. Override it if necessary:
#   make flash PORT=/dev/cu.usbmodem5CF90091131
#
# Always give west a port: without one, the Zephyr runner probes every
# serial port (Bluetooth, headsets, ...) and waits for timeouts (~9 s).

ZEPHYR_WORKSPACE ?= $(HOME)/zephyrproject
export ZEPHYR_BASE ?= $(ZEPHYR_WORKSPACE)/zephyr

# Put the venv first in PATH: west flash calls esptool from there.
VENV_BIN  := $(ZEPHYR_WORKSPACE)/.venv/bin
export PATH := $(VENV_BIN):$(PATH)

WEST      ?= $(VENV_BIN)/west
BOARD     ?= esp32s3_devkitc/esp32s3/procpu
BUILD_DIR ?= build
PORT      ?= $(firstword $(wildcard /dev/cu.usbmodem*))

# --esp-skip-flashed: skip the write when the flash already has this image.
PORT_ARG := $(if $(PORT),--esp-device $(PORT)) --esp-skip-flashed
MON_ARG  := $(if $(PORT),-p $(PORT))

.PHONY: all build pristine flash monitor run menuconfig clean

all: build

build:
	$(WEST) build -b $(BOARD) -d $(BUILD_DIR) .

# Delete the build folder first: a CMake cache from a moved or renamed
# folder makes "west build -p always" fail.
pristine: clean
	$(WEST) build -b $(BOARD) -d $(BUILD_DIR) .

flash: build
	$(WEST) flash -d $(BUILD_DIR) $(PORT_ARG)

monitor:
	$(WEST) espressif monitor $(MON_ARG)

run: flash monitor

menuconfig:
	$(WEST) build -d $(BUILD_DIR) -t menuconfig

clean:
	rm -rf $(BUILD_DIR)
