//Für die weitere Nutzung der Bibilothek siehe: https://abyz.me.uk/rpi/pigpio/cif.html

#include <pigpio.h>
#include <stdio.h>



int main() {

    int pin_led = 4;

    int secs = 10;

    if (gpioInitialise()<0) {
        return -1;
    }

    gpioSetMode(pin_led, PI_OUTPUT);

    while(secs > 0) {
        gpioWrite(pin_led, 1);
        time_sleep(1);
        gpioWrite(pin_led, 0);
        time_sleep(1);
        secs -= 2;
    }
    gpioTerminate();
}