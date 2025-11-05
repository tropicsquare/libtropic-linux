# TS1302 Devkit's Project
This project is compatible with Linux-based systems and our [USB devkit](https://github.com/tropicsquare/tropic01-stm32u5-usb-devkit-hw). Follow the link to get more details about this devkit, including schematics, design files, and manufacturing data.

## Clone

This repository must be cloned recursively because it contains `libtropic` as a submodule.

```bash
git clone https://github.com/tropicsquare/libtropic-linux.git
cd libtropic-linux
git submodule update --init --recursive
cd TS1302_devkit/
```

## Dependencies and Requirements

You need to have:
* Access to a USB UART interface (Linux `dialout` group or similar)
* `cmake` (On Debian-based systems, it can be installed with `sudo apt install cmake`)
* `gcc` (On Debian-based systems, it can be installed with `sudo apt install gcc`)

# Build All Examples

All examples are implemented in the [libtropic](https://github.com/tropicsquare/libtropic) repository. For more information about them, refer to the [Examples](https://tropicsquare.github.io/libtropic/latest/get_started/examples/) section in the libtropic documentation.

Build all examples in one place with the following commands:

```bash
mkdir build
cd build
cmake -DLT_CAL=mbedtls_v4 -DLT_BUILD_EXAMPLES=1 ..
make
```

For each example, a binary will be created in the build directory. Once all examples are built, continue with the following chapter.

# Recommended First Steps

> [!IMPORTANT]
> Before you start with various examples, we strongly recommend doing two things first:
> * Read the CHIP ID and TROPIC01's firmware versions and **save the printed output for future reference**.
> * Update both of TROPIC01's internal firmware to the latest version.

## Display and Save Chip ID and Firmware Versions

To display the current versions of internal firmware and details from the CHIP ID data field, execute the following example:

```bash
./lt_ex_show_chip_id_and_fwver
```

We recommend saving the printed output for future reference.

## Update Internal Firmware

To update both internal firmware to the latest versions, execute the following example:

```bash
./lt_ex_fw_update
```

After successful execution, your chip will contain the latest firmware and will be compatible with the `libtropic` API.

# Building and Running Other Examples

> [!WARNING]
> Some examples cause irreversible changes to the chip. For more details, refer to the [Examples](https://tropicsquare.github.io/libtropic/latest/get_started/examples/) section in the libtropic documentation.

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
> You may encounter issues with examples that establish a Secure Session - refer to [Establishing Your First Secure Channel Session](https://tropicsquare.github.io/libtropic/latest/get_started/default_pairing_keys/#establishing-your-first-secure-channel-session) section in libtropic documentation for more information.


# Building Functional Tests

All functional tests are implemented in the [libtropic](https://github.com/tropicsquare/libtropic) repository. For more information about them, refer to the [Functional Tests](https://tropicsquare.github.io/libtropic/latest/for_contributors/functional_tests/) section in the libtropic documentation.

> [!WARNING]
> Some tests make irreversible changes to the chip, such as writing pairing keys. Those irreversible tests contain `_ire_` in their name. On the other hand, reversible tests are marked `_rev_` and are generally safe to run, as they only make temporary changes and always perform cleanup.

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

If you encounter any issues, please have a look [here](./../FAQ.md) before filing an issue or reaching out to our [support](https://support.desk.tropicsquare.com/).
