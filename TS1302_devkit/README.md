# TS1302 Devkit's Project
This project is compatible with Linux-based systems (and possibly other POSIX-compatibles) and our [USB devkit](https://github.com/tropicsquare/tropic01-stm32u5-usb-devkit-hw). Follow the link to get more details about this devkit, including schematics, design files, and manufacturing data.

Contents:
- [TS1302 Devkit's Project](#ts1302-devkits-project)
  - [First Steps](#first-steps)
    - [Install Dependencies](#install-dependencies)
    - [System Setup](#system-setup)
    - [Clone the libtropic-linux Repository](#clone-the-libtropic-linux-repository)
    - [Build Examples](#build-examples)
    - [Run a Basic Example: Read CHIP ID and firmware versions](#run-a-basic-example-read-chip-id-and-firmware-versions)
    - [Update Internal Firmware](#update-internal-firmware)
  - [Running Advanced Examples](#running-advanced-examples)
  - [Building Functional Tests](#building-functional-tests)
  - [FAQ](#faq)

## First Steps
> [!IMPORTANT]
> **Do not skip these steps**. You will gather basic information about the chip (which you will need for any eventual support) and update your chip's firmware, which will guarantee compatibility with the latest Libtropic API.

Before proceeding, familiarize yourself with the [Libtropic SDK documentation](https://tropicsquare.github.io/libtropic/latest/).

### Install Dependencies
Make sure to have these dependencies installed:

* CMake
  * Raspbian/Debian/Ubuntu: `sudo apt install cmake`
  * Fedora: `sudo dnf install cmake`
* GCC
  * Raspbian/Debian/Ubuntu: `sudo apt install gcc`
  * Fedora: `sudo dnf install gcc`

### System Setup
Make sure you have access to a USB UART interface. Usually, your user account has to be a member of a certain group, usually the `dialout` group.

### Clone the libtropic-linux Repository

This repository must be cloned recursively because it contains [Libtropic](https://github.com/tropicsquare/libtropic) as a submodule.

```bash
git clone https://github.com/tropicsquare/libtropic-linux.git
cd libtropic-linux
git submodule update --init --recursive
cd TS1302_devkit/
```

### Build Examples

All examples are implemented in the [Libtropic](https://github.com/tropicsquare/libtropic) repository. For more information about them, refer to the [Examples](https://tropicsquare.github.io/libtropic/latest/get_started/examples/) section in the Libtropic SDK documentation.

Build all examples in one place with the following commands:

```bash
mkdir build
cd build
cmake -DLT_CAL=mbedtls_v4 -DLT_BUILD_EXAMPLES=1 ..
make
```

For each example, a binary will be created in the build directory. Once all examples are built, **continue with the following section**.

### Run a Basic Example: Read CHIP ID and firmware versions
First, it is recommended to run the **lt_ex_show_chip_id_and_fwver** example. This example will print, among other information, the CHIP ID and TROPIC01's firmware versions.

To run this example, execute:
```bash
./lt_ex_show_chip_id_and_fwver
```

Save the output of this example for future reference.

### Update Internal Firmware
After trying out communication and noting CHIP ID and firmware versions using the first example, upgrade TROPIC01's internal firmware, as newer versions fix bugs and ensure compatibility with the latest Libtropic SDK.

> [!IMPORTANT]
> Using outdated firmware is not recommended. Outdated firmware may not be compatible with the latest version of the Libtropic SDK.

To update both internal firmware to the latest versions, execute the following example:

```bash
./lt_ex_fw_update
```

After successful execution, your chip will contain the latest firmware and will be compatible with the current Libtropic API.

## Running Advanced Examples

> [!IMPORTANT]
> Make sure you have already run examples from previous sections.

> [!CAUTION]
> Some examples cause **irreversible changes** to the chip. Proceed only after you read the [Examples](https://tropicsquare.github.io/libtropic/latest/get_started/examples/) section in the Libtropic documentation and you understand the consequences. The documentation describes which examples are irreversible and what each example does.

Other examples can be run similarly to the ones you already tried. They are binaries, which you can simply execute.
```bash
./example_binary_name
```

> [!IMPORTANT]
> You may encounter issues with examples that establish a Secure Session — refer to [Establishing Your First Secure Channel Session](https://tropicsquare.github.io/libtropic/latest/get_started/default_pairing_keys/#establishing-your-first-secure-channel-session) in the Libtropic documentation for more information.

## Building Functional Tests

> [!CAUTION]
> **DANGER!** Functional tests are for internal use only and are provided only for reference. Some tests can **destroy** your chip. **Do not run the tests** unless you are absolutely sure what you are doing. If you damage your chip with the tests, we are unable to provide any support.

All functional tests are implemented in the [Libtropic](https://github.com/tropicsquare/libtropic) repository. For more information about them, refer to the [Functional Tests](https://tropicsquare.github.io/libtropic/latest/for_contributors/functional_tests/) section in the Libtropic documentation.

Build all functional tests in one place with the following commands:
```bash
mkdir build
cd build
cmake -DLT_CAL=mbedtls_v4 -DLT_BUILD_TESTS=1 ..
make
```

For each test, a binary will be created in the build directory (similarly as when building the examples).

> [!IMPORTANT]
> You may encounter issues with tests that establish a Secure Session - refer to [Establishing Your First Secure Channel Session](https://tropicsquare.github.io/libtropic/latest/get_started/default_pairing_keys/#establishing-your-first-secure-channel-session) section in libtropic documentation for more information.

We use CTest to run functional tests.

To list available tests:
```bash
ctest -N
```

To launch reversible tests only:
```bash
ctest -R _rev_
```

> [!TIP]
> To see all output, use `--verbose` or `-V`.

## FAQ

If you encounter any issues, please check [here](./../FAQ.md) before filing an issue or reaching out to our [support](https://support.desk.tropicsquare.com/).

> [!NOTE]
> Running tests is not officially supported. We do not provide any support for running tests.