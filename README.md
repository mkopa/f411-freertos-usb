# f411-freertos-usb

A demonstration project for the **STM32F411CEU6** microcontroller, built with **FreeRTOS** and using **USB CDC (Virtual COM Port)**. The project is managed using **Meson + Ninja** build system and can be used across **Linux**, **macOS**, and **Windows** (with appropriate tools installed).

## Features

* USB support in **CDC (Communication Device Class)** mode — the device appears as a virtual serial port (e.g. `/dev/ttyACM0`).
* Receive and echo back data over USB (terminal-like functionality).
* Integration with **FreeRTOS** — USB communication runs in a dedicated task.

## Requirements

* STM32F411CEU6 board with USB D+ and D- connected to PA12/PA11
* ARM Embedded Toolchain: `arm-none-eabi-gcc`, `arm-none-eabi-objcopy`, `arm-none-eabi-size`
* Meson (≥ 1.2), Ninja (≥ 1.10), Python 3
* OpenOCD (for flashing)

### Linux (Debian/Ubuntu)

```bash
sudo apt-get install openocd clang-format
```

You also need to install the ARM toolchain (if not installed):

```bash
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi
```

### macOS (using Homebrew)

```bash
brew install openocd clang-format arm-none-eabi-gcc meson ninja
```

> On macOS, ensure `PATH` includes `/opt/homebrew/bin` or equivalent for your architecture.

## Building the project

1. Configure the Meson build environment:

   ```bash
   meson setup build --cross-file cross_file.txt
   ```

2. Compile the project:

   ```bash
   meson compile -C build
   ```

3. (Optional) Format application source files:

   ```bash
   meson compile -C build format-app
   ```

4. Flash the device using OpenOCD:

   ```bash
   ninja -C build flash
   ```

## Project structure

```
├── App/                # User application logic (FreeRTOS tasks, USB echo)
├── Core/               # HAL/STM32CubeMX core files (minimally modified)
├── Drivers/            # STM32 HAL and CMSIS drivers
├── Middlewares/        # FreeRTOS and STM32 USB Device Library
├── USB_DEVICE/         # USB stack configuration
├── meson.build         # Meson build script
├── cross_file.txt      # Toolchain definition (to be customized)
└── README.md           # This file
```

## Notes

* The build process generates `.hex` and `.bin` firmware files.
* CDC device appears as `/dev/ttyACM*` (Linux), `/dev/cu.usbmodem*` (macOS), or `COMx` (Windows).
* Main application task is implemented in `App/Src/app.c`.

---

📬 If you have questions or need help integrating other peripherals (UART, SPI, sensors), feel free to ask!
