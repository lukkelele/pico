#include "pico_dc_motor.h"

constexpr int sleep_time = 2000;

DCMotor::DCMotor()
{
}

void DCMotor::Init()
{
    gpio_init(FORWARD_PIN);
    gpio_set_dir(FORWARD_PIN, GPIO_OUT);

    // Pico onboard LED
    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);
    // gpio_put(ONBOARD_LED, 1);
}

void DCMotor::OnUpdate()
{
    if (IsButtonPressed(FORWARD_BUTTON))
    {
        Forward(MAX_POWER);
    }

    else
    {
        Neutral();
    }
}

void DCMotor::SetLED(uint pin, int val)
{
    gpio_put(pin, val);
}

void DCMotor::ToggleLED(uint pin)
{
    uint val = gpio_get(pin);
    if (val == 0)
    {
        gpio_put(pin, 1);
        return;
    }
    gpio_put(pin, 0);
}

void DCMotor::Forward(float p)
{
    if (m_Forward == false)
    {
        m_Forward = true;
        gpio_put(FORWARD_PIN, 1);
    }
}

void DCMotor::Backward(float p)
{
}

void DCMotor::Neutral()
{
    gpio_put(FORWARD_PIN, 0);
    m_Forward = false;
}

bool DCMotor::IsButtonPressed(uint button)
{
    int buttonVal = gpio_get(button);
    return buttonVal == 1;
}

int main()
{
    // setup_default_uart();
    stdio_init_all();
    printf("Hello World\n");

    const uint LED_PIN = 25;
    const uint PIN_15 = 15;
    gpio_init(LED_PIN);
    gpio_init(PIN_15);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(PIN_15, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    gpio_put(PIN_15, 1);

    while (true)
    {
        // LED ON
        gpio_put(LED_PIN, 1);
        gpio_put(PIN_15, 1);
        printf("LED ON\n");
        sleep_ms(sleep_time);

        // LED OFF
        gpio_put(LED_PIN, 0);
        gpio_put(PIN_15, 0);
        printf("LED OFF\n");
        sleep_ms(sleep_time);
    }

    return 0;
}

