# Linux SPI Project
This port should be compatible with most Linux-based systems with a hardware SPI interface, including popular single-board computers such as the Raspberry Pi. It is compatible with our [Raspberry Pi shield](https://github.com/tropicsquare/tropic01-raspberrypi-shield-hw). Follow the link to get more details about this shield, including schematics, design files, and manufacturing data.

- [Linux SPI Project](#linux-spi-project)
  - [Clone](#clone)
  - [Dependencies and Requirements](#dependencies-and-requirements)
- [Quick Start](#quick-start)
  - [1. Hardware Preparation](#1-hardware-preparation)
  - [2. Build All Examples](#2-build-all-examples)
  - [3. Display and Save Chip ID and FW Versions](#3-display-and-save-chip-id-and-fw-versions)
  - [4. Update Internal Firmware](#4-update-internal-firmware)
  - [5. Build and Run Other Examples](#5-build-and-run-other-examples)
  - [6. Build and Run Functional Tests](#6-build-and-run-functional-tests)
- [FAQ](#faq)

## Clone

This repository must be cloned recursively because it contains `libtropic` as a submodule.

```bash
git clone https://github.com/tropicsquare/libtropic-linux.git
cd libtropic-linux
git submodule update --init --recursive
```

## Dependencies and Requirements
You need to have:
* The SPI kernel module enabled.
    * On Raspberry Pi, you can use `raspi-config` to enable the module.
* Permissions to access the SPI interface.
    * On Raspberry Pi, you must be a member of the `spi` group.
* `cmake` (On Debian-based systems, it can be installed with `sudo apt install cmake`).
* `gcc` (On Debian-based systems, it can be installed with `sudo apt install gcc`).

# Quick Start
We encourage new users to do the following steps.

## 1. Hardware Preparation
As stated above, we recommend using our [Raspberry Pi Shield](https://github.com/tropicsquare/tropic01-raspberrypi-shield-hw).
> [!IMPORTANT]
On the shield, short the CS2 pins with a jumper.


Your setup should look like the following:

<img src="img/rpi_shield_setup_1.jpg" alt="RPi Shield Setup Top" width="400"/>

<img src="img/rpi_shield_setup_2.jpg" alt="RPi Shield Setup Side" width="400"/>

## 2. Build All Examples

All available examples are taken from [libtropic](https://github.com/tropicsquare/libtropic/tree/master/examples).

Build all examples in one place with the following commands:

```bash
mkdir build
cd build
cmake -DLT_BUILD_EXAMPLES=1 ..
make
```

For each example, a binary will be created in the build directory.

> [!IMPORTANT]
> Before you start with various examples, we strongly recommend doing two things first:
> * Read the CHIP ID and TROPIC01's firmware versions and **save the printed output for future reference**.
> * Update TROPIC01's internal firmware to the latest version.
>
> For that, continue to the next two sections.

## 3. Display and Save Chip ID and FW Versions
To display the current versions of internal firmwares (SPECT and Application) and details from the CHIP ID data field, execute the following example:
```bash
./lt_ex_show_chip_id_and_fwver
```

We recommend saving the the printed output for future reference.

## 4. Update Internal Firmware

To update both internal firmware to the latest versions, execute the following example:

```bash
./lt_ex_fw_update
```

After successful execution, your chip will contain the latest firmware and will be compatible with the `libtropic` API.

## 5. Build and Run Other Examples

> [!WARNING]
> Some examples cause irreversible changes to the chip. For more details, read the [libtropic examples readme](https://github.com/tropicsquare/libtropic/tree/master/examples).

For each built example, a binary is created in the build directory. For example, upon running the `lt_ex_hello_world` example as:

```bash
./lt_ex_hello_world
```

You should see output similar to this:

```bash
INFO    [  21] ======================================
INFO    [  22] ==== TROPIC01 Hello World Example ====
INFO    [  23] ======================================
INFO    [  27] Initializing handle
INFO    [  35] Starting Secure Session with key 0
INFO    [  43] 	-------------------------------------------------
INFO    [  46] Sending Ping command with message:
INFO    [  47] 	"This is Hello World message from TROPIC01!!"
INFO    [  55] 	-------------------------------------------------
INFO    [  57] Message received from TROPIC01:
INFO    [  58] 	"This is Hello World message from TROPIC01!!"
INFO    [  59] 	-------------------------------------------------
INFO    [  61] Aborting Secure Session
INFO    [  69] Deinitializing handle
```

> [!IMPORTANT]
> During the build, the SH0 keypair is automatically chosen from `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. This SH0 key is present in the majority of distributed TROPIC01 chips. In certain cases (e.g., first engineering samples), it might be necessary to manually set it (in PEM or DER format) with the following CMake switch: `-DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem`.

## 6. Build and Run Functional Tests

All available functional tests can be found [here](https://github.com/tropicsquare/libtropic/tree/master/tests/functional/).

> [!WARNING]
> Some tests make irreversible changes to the chip, such as writing pairing keys. Those irreversible tests contain `_ire_` in their name. On the other hand, reversible tests are marked `_rev_` and are generally safe to run, as they only make temporary changes and always perform cleanup.

Build all functional tests in one place with the following commands:
```bash
mkdir build
cd build
cmake -DLT_BUILD_TESTS=1 ..
make
```

For each test, a binary will be created in the build directory (similarly as when building the examples).

> [!IMPORTANT]
> During the build, the SH0 keypair is automatically chosen from `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. This SH0 key is present in the majority of distributed TROPIC01 chips. In certain cases (e.g., first engineering samples), it might be necessary to manually set it (in PEM or DER format) with the following CMake switch: `-DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem`.

We recommend using CTest for handling functional tests.

To show available tests:

```bash
ctest -N
```

To launch all tests (some of them are irreversible):

```bash
ctest
```

To launch a selected test:

```bash
ctest -R test_name
```

> [!TIP]
> To see all output, use `--verbose`.

# FAQ

If you encounter any issues, please check [here](./../FAQ.md) before filing an issue or reaching out to our [support](https://support.desk.tropicsquare.com/).