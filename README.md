# libtropic-linux

This repository contains examples of the official SDK [`libtropic`](https://github.com/tropicsquare/libtropic)'s usage on Linux-based platforms.

Contributors, please follow the [guidelines](https://github.com/tropicsquare/libtropic-linux/blob/master/CONTRIBUTING.md).

 > [!IMPORTANT]
 > Example projects in separate folders represent different hardware connections for TROPIC01. They all wrap [`libtropic`](https://github.com/tropicsquare/libtropic) and are ready to be compiled and executed in a Linux environment.

### Supported Hardware

[Tropic Square](https://www.tropicsquare.com) provides [TROPIC01](https://www.tropicsquare.com/tropic01) not only as a **silicon chip** but also as **various shields** and **devkits**, so the building instructions differ.

 > [!IMPORTANT]
 > Before starting with the examples, we strongly recommend completing the following steps:
 > * Read the CHIP ID and TROPIC01's firmware versions, and **save the printed output for future reference**.
 > * Update both of TROPIC01's internal firmware components to the latest version.
 
Choose the instructions based on the hardware you want to use:
* [Linux SPI](./Linux_SPI/README.md) (compatible with our [Raspberry Pi shield](https://github.com/tropicsquare/tropic01-raspberrypi-shield-hw))
* [USB devkit TS1302](./TS1302_devkit/README.md) (compatible with our [USB devkit](https://github.com/tropicsquare/tropic01-stm32u5-usb-devkit-hw))

### License

See the [LICENSE.md](LICENSE.md) file in the root of this repository or consult the license information on the [Tropic Square website](https://tropicsquare.com/license).

### FAQ

If you encounter any issues, please check [here](./FAQ.md) before filing an issue or reaching out to our [support](https://support.desk.tropicsquare.com/).

