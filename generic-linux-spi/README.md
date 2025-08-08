# generic-linux-spi port
This port should be compatible with most Linux-based system with hardware SPI interface, including
popular single-board computers such as the Raspberry Pi.

## Dependencies and Requirements
Additionally to common dependecies specified in root [`README.md`](../README.md), you need:

* SPI kernel module enabled.
    * On Raspberry Pi you can use `raspi-config` to enable the module.
* Permissions to access the SPI interface.
    * On Raspberry Pi you have to be a member of the `spi` group.
