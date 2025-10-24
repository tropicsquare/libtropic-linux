# FAQ

This list might help you resolve some issues.

- [FAQ](#faq)
  - [The SPI is not working.](#the-spi-is-not-working)
  - [Cannot establish a secure session?](#cannot-establish-a-secure-session)

None of the above helped?
- If you are a customer, contact Tropic Square via the [Support Portal](http://support.tropicsquare.com) or contact your business partners.  
- Otherwise, [open an issue](https://github.com/tropicsquare/libtropic-linux/issues/new/choose).

## The SPI is not working.
You may need to activate the kernel module using `raspi-config`. Check out [this tutorial](https://www.raspberrypi-spy.co.uk/2014/08/enabling-the-spi-interface-on-the-raspberry-pi/).

## Cannot establish a secure session?
You might be using wrong default pairing keys - refer to [Default Pairing Keys for a Secure Channel Handshake](https://tropicsquare.github.io/libtropic/latest/get_started/default_pairing_keys/) section in libtropic documentation for more information.