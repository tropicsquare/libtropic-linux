/**
 * @file main.c
 * @author Tropic Square s.r.o.
 *
 * @license For the license see file LICENSE.txt file in the root directory of this source tree.
 */


#include <string.h>

#include "libtropic.h"
#include "libtropic_port.h"
#include "libtropic_common.h"
#include "libtropic_functional_tests.h"

int main(int argc, char *argv[]) {

    // This will setup mappings compatible with RPi and our RPi shield.
    lt_dev_unix_spi_t device = {0};
    strcpy(device.gpio_dev, "/dev/gpiochip0");
    strcpy(device.spi_dev, "/dev/spidev0.0");
    device.spi_speed = 1000000; // 1 MHz
    device.gpio_cs_num = 25;    // GPIO 25 as on RPi shield.

    lt_handle_t __lt_handle__;
    __lt_handle__.l2.device = &device;

    #ifdef LT_BUILD_TESTS
    #include "lt_test_registry.c.inc"
    #endif

    // When examples are being built, special variable containing example return value is defined.
    // Otherwise, 0 is always returned (in case of building tests).
    #ifdef LT_BUILD_EXAMPLES
    #include "lt_ex_registry.c.inc"
        return __lt_ex_return_val__;
    #else
        return 0;
    #endif
}