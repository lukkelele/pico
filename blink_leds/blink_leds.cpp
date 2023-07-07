#include "Base.h"

constexpr int sleep_time = 500;


int main()
{
    stdio_init_all();
    
    printf("Starting...\n");
    gpio_init(ONBOARD_LED);
    gpio_init(PIN_15);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);
    gpio_set_dir(PIN_15, GPIO_OUT);
    gpio_put(ONBOARD_LED, 1);

    gpio_init(PIN_6);
    gpio_set_dir(PIN_6, GPIO_IN);

    while (true)
    {
        // LED ON
        gpio_put(ONBOARD_LED, 1);
        // gpio_put(PIN_15, 1);
        printf("LED ON\n");
        sleep_ms(sleep_time);

        // LED OFF
        gpio_put(ONBOARD_LED, 0);
        // gpio_put(PIN_15, 0);
        printf("LED OFF\n");
        sleep_ms(sleep_time);

        int buttonValue = gpio_get(PIN_6);
        // TODO: Fix switch bouncing
        if (buttonValue == 1)
        {
            gpio_put(PIN_15, 1);
        }
        else
        {
            gpio_put(PIN_15, 0);
        }
    }

    return 0;
}

