#include <stdio.h>
#include <unistd.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>

#define ONBOARD_LED 25   
#define PIN_6 6
#define PIN_15 15

#define BITFIELD(x)        (1 << x)
#define SET_BIT(x, pos)    (x |= (1U << pos))
#define CLEAR_BIT(x, pos)  (x &= (~(1U << pos)))
#define TOGGLE_BIT(x, pos) (x ^= (1U<< pos))


static bool IsButtonPressed(uint button)
{
    int buttonVal = gpio_get(button);
    return buttonVal == 1;
}
