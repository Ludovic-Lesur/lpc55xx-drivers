# Description

This repository contains the **peripherals drivers** of the LPC55xx MCUs.

# Dependencies

The drivers rely on:

* The **LPC55xx linker scripts** defined in the [lpc55xx-device](https://github.com/Ludovic-Lesur/lpc55xx-device) repository.
* The **LPC55xx registers** defined in the [lpc55xx-registers](https://github.com/Ludovic-Lesur/lpc55xx-registers) repository.
* The **embedded utility functions** defined in the [embedded-utils](https://github.com/Ludovic-Lesur/embedded-utils) repository.

Here is the versions compatibility table:

| **lpc55xx-drivers** | **lpc55xx-device** | **lpc55xx-registers** | **embedded-utils** |
|:---:|:---:|:---:|:---:|
| [sw1.0](https://github.com/Ludovic-Lesur/lpc55xx-drivers/releases/tag/sw1.0) | >= [sw1.0](https://github.com/Ludovic-Lesur/lpc55xx-device/releases/tag/sw1.0) | >= [sw1.0](https://github.com/Ludovic-Lesur/lpc55xx-registers/releases/tag/sw1.0) | >= [sw7.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw7.0) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `LPC55XX_DRIVERS_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `lpc55xx_drivers_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `LPC55XX_DRIVERS_SYSCON_XO32M_FREQUENCY_HZ` | `<value>` | Defines the external high speed crystal frequency in Hz. |
| `LPC55XX_DRIVERS_SYSCON_XTAL32K_FREQUENCY_HZ` | `<value>` | Defines the external low speed crystal frequency in Hz. |
