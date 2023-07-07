#include "pico_dc_motor.h"


DCMotor::DCMotor()
{
}

void DCMotor::Init()
{
    gpio_init(ONBOARD_LED);
    gpio_init(PIN_15);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);
    gpio_set_dir(PIN_15, GPIO_OUT);

    gpio_put(ONBOARD_LED, 1);
    // Light green LED before initializing PWM
    gpio_put(PIN_15, 1); 
    InitPWM(PWM_PIN, PWM_RANGE);
    gpio_put(PIN_15, 0); 
}

void DCMotor::OnUpdate()
{
}

void DCMotor::InitPWM(uint pin, float pwm_range)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    m_SliceNum = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(m_SliceNum, pwm_range);
    pwm_set_clkdiv(m_SliceNum, 2.0f);
    pwm_set_enabled(m_SliceNum, true);
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
    // TODO: Checker for same value - skip if same
    m_Forward = true;
    pwm_set_chan_level(m_SliceNum, PWM_CHAN_A, p);
}

void DCMotor::Backward(float p)
{
    pwm_set_chan_level(m_SliceNum, PWM_CHAN_A, -p);
}

void DCMotor::Neutral()
{
    m_Forward = false;
    pwm_set_chan_level(m_SliceNum, PWM_CHAN_A, 0);
}

void DCMotor::UpdateDutyCycle(bool forward)
{
    if (forward)
    {
        m_DutyCycle++;
        return;
    }
    m_DutyCycle--;
}

void DCMotor::SetDutyCycle(int cycle)
{
    m_DutyCycle = cycle;
}

bool DCMotor::IsButtonPressed(uint button)
{
    int buttonVal = gpio_get(button);
    return buttonVal == 1;
}

int main()
{
    stdio_init_all();
    
    printf("Hello World\n");


    DCMotor dcMotor;
    dcMotor.Init();

    while (true)
    {
        gpio_put(PIN_15, 1); // Green LED
        for (uint dutyCycle = 0; dutyCycle <= PWM_RANGE; dutyCycle++)
        {
            dcMotor.SetDutyCycle(dutyCycle);
            pwm_set_chan_level(dcMotor.GetDutyCycle(), PWM_CHAN_A, dutyCycle);
            sleep_ms(10);
        }
        gpio_put(PIN_15, 0);

        for (uint dutyCycle = PWM_RANGE; dutyCycle > 0; dutyCycle--)
        {
            dcMotor.SetDutyCycle(dutyCycle);
            pwm_set_chan_level(dcMotor.GetDutyCycle(), PWM_CHAN_A, dutyCycle);
            sleep_ms(10);
        }

        // LED ON
        gpio_put(ONBOARD_LED, 1);
        gpio_put(PIN_15, 1);
        printf("LED ON\n");
        sleep_ms(sleep_time);

        // LED OFF
        gpio_put(ONBOARD_LED, 0);
        gpio_put(PIN_15, 0);
        printf("LED OFF\n");
        sleep_ms(sleep_time);
    }

    return 0;
}

