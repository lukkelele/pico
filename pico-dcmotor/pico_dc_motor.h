#ifndef PICO_DC_MOTOR_H
#define PICO_DC_MOTOR_H
#include <stdio.h>
#include <unistd.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

#define FORWARD_PIN 15   // GPIO 15
#define FORWARD_BUTTON 6 // GPIO 6
#define ONBOARD_LED 25   // GPIO 25
constexpr float MAX_POWER = 1.0f;
constexpr float MIN_POWER = 0.0f;

class DCMotor 
{
public:
    DCMotor();
    ~DCMotor() = default;

    void Init();
    void Shutdown();
    void OnUpdate();

    void SetLED(uint pin, int val);
    void ToggleLED(uint pin);
    // Float 'p' to adjust power delivery, within range 0..1
    void Forward(float p);
    void Backward(float p);
    void Neutral();
    bool IsButtonPressed(uint button);

private:
    bool m_Forward = false;
};


#endif /* PICO_DC_MOTOR_H */
