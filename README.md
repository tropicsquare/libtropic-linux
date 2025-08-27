# libtropic-linux

This repository contains examples of our official SDK [`libtropic`](https://github.com/tropicsquare/libtropic)'s usage on Linux-based platforms.

Contributors, please follow [guidelines](https://github.com/tropicsquare/libtropic-stm32/blob/master/CONTRIBUTING.md).


## Clone

This repository must be cloned recursively, because it contains libtropic as a submodule.

```bash
git clone https://github.com/tropicsquare/libtropic-linux.git
cd libtropic-linux
git submodule update --init --recursive
```

### Supported hardware

Example projects in separate folders represent different hardware connections of TROPIC01. They all wrap [`libtropic`](https://github.com/tropicsquare/libtropic) and are ready to be compiled and executed under linux environment. Because [Tropic Square](https://www.tropicsquare.com) provides not only [TROPIC01](https://www.tropicsquare.com/tropic01) in a form of a **silicon chip**, but also in a form of **various shields** and **devkits**, building instructions differ.

Choose instruction based on hardware you want to use:
* [Raspberrypi shield](./generic-linux-spi/README.md) (also compatible with linux systems where SPI interface is connected directly to chip)
* [USB devkit TS1302](./generic-linux-usb-dongle/README.md)


Hardware details about various devkits and shields including schematics, design files and manufacturing data can be found here:
* [USB devkit](https://github.com/tropicsquare/tropic01-stm32u5-usb-devkit-hw)
* [Raspberrypi shield](https://github.com/tropicsquare/tropic01-raspberrypi-shield-hw)

### License

See the [LICENSE.md](LICENSE.md) file in the root of this repository or consult license information at [Tropic Square website](https://tropicsquare.com/license).