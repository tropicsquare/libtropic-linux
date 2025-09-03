# FAQ

This list might help you resolve some issues.

- [FAQ](#faq)
  - [The SPI is not working.](#the-spi-is-not-working)
  - [The Secure Session cannot be established, or the chip does not respond.](#the-secure-session-cannot-be-established-or-the-chip-does-not-respond)

None of the above helped?
- If you are a customer, contact Tropic Square via the [Support Portal](http://support.tropicsquare.com) or contact your business partners.  
- Otherwise, [open an issue](https://github.com/tropicsquare/libtropic-linux/issues/new/choose).

## The SPI is not working.
You may need to activate the kernel module using `raspi-config`. Check out [this tutorial](https://www.raspberrypi-spy.co.uk/2014/08/enabling-the-spi-interface-on-the-raspberry-pi/).

## The Secure Session cannot be established, or the chip does not respond.
Be aware of which revision of the chip you are using. The chip revisions are called ABAB for Engineering Samples and ACAB (or newer) for Production Silicon.

Run the following example to identify which silicon revision you have available:
```sh
./lt_ex_show_chip_id_and_fwver
```

Note that by default, keys for Production Silicon are used. If you need to use an Engineering Sample for some reason, compile with the appropriate keys like this:
```sh
rm -rf build
mkdir build
cd build
cmake -DLT_BUILD_EXAMPLES=1 -DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem ..
make
```