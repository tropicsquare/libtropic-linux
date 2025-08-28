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

 > [!IMPORTANT]
 > Example projects in separate folders represent different hardware connections of TROPIC01. They all wrap [`libtropic`](https://github.com/tropicsquare/libtropic) and are ready to be compiled and executed under Linux environment.

### Supported Hardware

Because [Tropic Square](https://www.tropicsquare.com) provides not only [TROPIC01](https://www.tropicsquare.com/tropic01) in a form of a **silicon chip**, but also in a form of **various shields** and **devkits**, building instructions differ.

 > [!IMPORTANT]
 > Before you start with various examples, we strongly recommend to do two things first:
 > * Read CHIP ID and TROPIC01's firmware versions and **save printed output for future reference**
 > * Update TROPIC01's both internal firmware to latest version.
 
Choose instruction based on hardware you want to use:
* [Raspberrypi shield](./Linux_SPI/README.md) (also compatible with Linux systems where SPI interface is connected directly to chip)
* [USB devkit TS1302](./TS1302_devkit/README.md)

### License

See the [LICENSE.md](LICENSE.md) file in the root of this repository or consult license information at [Tropic Square website](https://tropicsquare.com/license).