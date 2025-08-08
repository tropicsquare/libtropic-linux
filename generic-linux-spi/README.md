# generic-linux-spi port
This port should be compatible with most Linux-based system with hardware SPI interface, including
popular single-board computers such as the Raspberry Pi.

## Dependencies and Requirements
Additionally to common dependecies specified in root [`README.md`](../README.md), you need:

* SPI kernel module enabled.
    * On Raspberry Pi you can use `raspi-config` to enable the module.
* Permissions to access the SPI interface.
    * On Raspberry Pi you have to be a member of the `spi` group.

## Using with Raspberry Pi (barebones or using our shield)
If you use our [official TS15 shield](https://github.com/tropicsquare/ts-dev-kits/blob/main/ts1501-rpi-shield.md),
put jumper on CS2 position and you are ready to go.

If you do not have our shield or you want to connect the chip manually, wire TROPIC01 according to
following diagram:

```
                    Connector J8 on Raspberry Pi:
         3v3  -->        3V3  (1) (2)  5V    
                       GPIO2  (3) (4)  5V    
                       GPIO3  (5) (6)  GND   
                       GPIO4  (7) (8)  GPIO14
         GND  -->        GND  (9) (10) GPIO15
                      GPIO17 (11) (12) GPIO18
                      GPIO27 (13) (14) GND   
                      GPIO22 (15) (16) GPIO23
                         3V3 (17) (18) GPIO24
         MOSI -->     GPIO10 (19) (20) GND   
         MISO -->      GPIO9 (21) (22) GPIO25    <--  CS
          CLK -->     GPIO11 (23) (24) GPIO8 
                         GND (25) (26) GPIO7 
                       GPIO0 (27) (28) GPIO1 
                       GPIO5 (29) (30) GND   
                       GPIO6 (31) (32) GPIO12
                      GPIO13 (33) (34) GND   
                      GPIO19 (35) (36) GPIO16
                      GPIO26 (37) (38) GPIO20
                         GND (39) (40) GPIO21

```

> [!NOTE]
> Note that GPIO25 is intentionally used for chip select, as we control chip select manually.
> Do not connect TROPIC01's chip select anywhere else, unless you change default settings in `main.c`
> (and you know what are you doing).