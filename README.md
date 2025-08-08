# libtropic-linux

## About

This repository contains examples of libtropic's usage on Linux-based platforms.

Contributors, please follow [guidelines](https://github.com/tropicsquare/libtropic-stm32/blob/master/CONTRIBUTING.md).

We support multiple backends for communication with the Tropic01 chip:
* [Generic SPI driver](./generic-linux-spi/README.md)
    * Compatible with Linux-based systems with SPI interface including Raspberry Pi.
* [UART driver for TS13 USB dongle](./generic-linux-usb-dongle/README.md)
    * Compatible only with our [TS13 dongle](https://github.com/tropicsquare/ts-dev-kits/blob/main/ts1302-usb-dev-kit.md).

## Dependencies
* cmake
* gcc

Each backend may have its own additional dependencies and requirements. Check out README.md in the backend's directory.

## Cloning

This repository must be cloned recursively, because it contains libtropic as a submodule.

```bash
git clone https://github.com/tropicsquare/libtropic-linux.git
cd libtropic-linux
git submodule update --init --recursive
```

## Compiling and Running Examples

To compile all examples, pass `-DLT_BUILD_EXAMPLES=1` to CMake.
```bash
cmake -DLT_BUILD_EXAMPLES=1 ..
```
> [!NOTE]
> Examples require SH0 private key to establish a secure session with TROPIC01. CMake variable `LT_SH0_PRIV_PATH` is used for that and its default value is set to path to the SH0 private key from the currently used `lab_batch_package`, found in `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. Naturally, it can be overridden with another path to SH0 private key.

All available examples are [here](https://github.com/tropicsquare/libtropic/tree/master/examples).

All steps to build examples using the Generic SPI backend:
```bash
cd generic-linux-spi/
mkdir build
cd build
cmake -DLT_BUILD_EXAMPLES=1 ..
make
```

Each example will be compiled as a separate binary in the build directory. Just run any example as
an any other executable:
```bash
./lt_ex_hello_world
```

You will see some output on stdout similar to this:
```
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

## Building Functional Tests
To build functional test suite from libtropic, pass `-DLT_BUILD_TESTS=1` to CMake:
```bash
cmake -DLT_BUILD_TESTS=1 ..
```

> [!NOTE]
> Functional tests require SH0 private key to establish a secure session with TROPIC01. CMake variable `LT_SH0_PRIV_PATH` is used for that and its default value is set to path to the SH0 private key from the currently used `lab_batch_package`, found in `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. Naturally, it can be overridden with another path to SH0 private key.

For each test, a binary will be created in the build directory. Normally, we use CTest for handling the functional tests.

To launch all tests:
```bash
ctest
```
*Tip: To see all output use `--verbose`.*

To launch a selected test:
```bash
ctest -R test_name
```

To enumerate tests:
```bash
ctest -N
```

## License

See the [LICENSE.md](LICENSE.md) file in the root of this repository or consult license information at [Tropic Square website](https://tropicsquare.com/license).