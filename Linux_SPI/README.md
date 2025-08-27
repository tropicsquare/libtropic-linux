# Linux SPI project
This port should be compatible with most Linux-based system with hardware SPI interface, including
popular single-board computers such as the Raspberry Pi. It is compatible with our [Raspberrypi shield](https://github.com/tropicsquare/tropic01-raspberrypi-shield-hw) - follow the link to get more details about this shield itself, including schematics, design files and manufacturing data.

## Dependencies and Requirements

You need to have:
* SPI kernel module enabled.
    * On Raspberry Pi you can use `raspi-config` to enable the module.
* Permissions to access the SPI interface.
    * On Raspberry Pi you have to be a member of the `spi` group.
* `cmake` (Could be installed with `sudo apt install cmake`)
* `gcc` (Could be installed with `sudo apt install gcc`)


# Build All Examples

All available examples are taken from [`libtropic`](https://github.com/tropicsquare/libtropic/tree/master/examples).

Build all examples in one place with following commands:

```bash
mkdir build
cd build
cmake -DLT_BUILD_EXAMPLES=1 ..
make
```
For each example, a binary will be created in the build directory. Once all examples are built, continue with following chapter.

# Recommended First Steps

> [!IMPORTANT]
> Before further evaluation, first display and save your TROPIC01's chip ID and firmware versions for future and then update TROPIC01 chip to latest firmwares!

## Display And Save Chip ID And Fw Versions
To display actual versions of internal firmwares and details from CHIP ID data field, execute following example:
```bash
./lt_ex_show_chip_id_and_fwver
```
We recommend to save printed output for future reference.

## Update Internal Firmwares

To update both internal firmwares to latest versions execute following example:
```bash
./lt_ex_fw_update
```

After successfull execution your chip will contain latest firmwares and will be compatible with libtropic API.



## Building and Running Other Examples

```
For each built example, a binary was created in the build directory. For example, upon running the `lt_ex_hello_world` example as:
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

> [!WARNING]
> Some examples causes irreversible changes to chip. For more detail read [`README.md`](libtropic/examples/README.md).

## Building Functional Tests

 > [!NOTE]
 > This is for developers only.

All available functional tests can be found [here](https://github.com/tropicsquare/libtropic/tree/master/tests/functional/).

> [!WARNING]
> Some tests make irreversible changes to the chip, such as writing pairing keys. Those irreversible
> tests contain `_ire_` in their name. On the other hand, reversible tests are marked `_rev_`
> and are generally safe to run, as they do only temporary changes and always do a clean up.

To build functional tests do the following:
```bash
mkdir build
cd build
cmake -DLT_BUILD_TESTS=1 ..
make
```

For each test, a binary will be created in the build directory, the same as when building examples.

> [!IMPORTANT]
> When `LT_BUILD_TESTS` are set, there has to be a way to define the SH0 private key for the TROPIC01's pairing key slot 0, because both the examples and the tests depend on it. For this purpose, the CMake variable `LT_SH0_PRIV_PATH` is used, which should hold the path to the file with the SH0 private key in PEM or DER format. By default, the path is set to the currently used lab batch package, found in `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. But it can be overriden by the user either from the command line when executing CMake (switch `-DLT_SH0_PRIV_PATH=<path>`), or from a child CMakeLists.txt.

We recommend to use CTest for handling of functional tests.

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
> To see all output use `--verbose`.
