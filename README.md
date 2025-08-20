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

## Building and Running Examples
All available examples can be found [here](https://github.com/tropicsquare/libtropic/tree/master/examples).

To build examples, switch to one of the target directories (in this case, the `generic-linux-spi` target), and do the following:
```bash
cd generic-linux-spi/
mkdir build
cd build
cmake -DLT_BUILD_EXAMPLES=1 ..
make
```
For each example, a binary will be created in the build directory. For example, upon running the `lt_ex_hello_world` example as:
```bash
./lt_ex_hello_world
```
you should see some output similar to this:
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

> [!IMPORTANT]
> When `LT_BUILD_EXAMPLES` are set, there has to be a way to define the SH0 private key for the TROPIC01's pairing key slot 0, because both the examples and the tests depend on it. For this purpose, the CMake variable `LT_SH0_PRIV_PATH` is used, which should hold the path to the file with the SH0 private key in PEM or DER format. By default, the path is set to the currently used lab batch package, found in `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. But it can be overriden by the user either from the command line when executing CMake (switch `-DLT_SH0_PRIV_PATH=<path>`), or from a child CMakeLists.txt.

## Building Functional Tests
All available functional tests can be found [here](https://github.com/tropicsquare/libtropic/tree/master/tests/functional/).

> [!WARNING]
> Some tests make irreversible changes to the chip, such as writing pairing keys. Those irreversible
> tests contain `_ire_` in their name. On the other hand, reversible tests are marked `_rev_`
> and are generally safe to run, as they do only temporary changes and always do a clean up.

To build functional tests, switch to one of the target directories (in this case, the `generic-linux-spi` target), and do the following:
```bash
cd generic-linux-spi/
mkdir build
cd build
cmake -DLT_BUILD_TESTS=1 ..
make
```

For each test, a binary will be created in the build directory.

> [!IMPORTANT]
> When `LT_BUILD_TESTS` are set, there has to be a way to define the SH0 private key for the TROPIC01's pairing key slot 0, because both the examples and the tests depend on it. For this purpose, the CMake variable `LT_SH0_PRIV_PATH` is used, which should hold the path to the file with the SH0 private key in PEM or DER format. By default, the path is set to the currently used lab batch package, found in `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. But it can be overriden by the user either from the command line when executing CMake (switch `-DLT_SH0_PRIV_PATH=<path>`), or from a child CMakeLists.txt.

Normally, we use CTest for handling the functional tests.

To launch all tests:
```bash
ctest
```
> [!TIP]
> To see all output use `--verbose`.

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