#ifndef PICO_DC_MOTOR_H
#define PICO_DC_MOTOR_H
#include <stdio.h>
#include <unistd.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>

#define FORWARD_PIN 15 
#define FORWARD_BUTTON 6
#define ONBOARD_LED 25   
#define PWM_PIN 16
#define PIN_15 15

constexpr int sleep_time = 2000;
constexpr float MAX_POWER = 1.0f;
constexpr float MIN_POWER = 0.0f;
constexpr uint PWM_FREQ = 10000;
constexpr uint PWM_RANGE = 255;

class DCMotor 
{
public:
    DCMotor();
    ~DCMotor() = default;

    void Init();
    void Shutdown();
    void OnUpdate();

    void ToggleLED(uint pin);
    // Float 'p' to adjust power delivery, within range 0..1
    void Forward(float p);
    void Backward(float p);
    void Neutral();
    bool IsButtonPressed(uint button);
    void UpdateDutyCycle(bool forward);
    void SetDutyCycle(int cycle);
    int GetDutyCycle() const { return m_DutyCycle; }

private:
    void InitPWM(uint pin, float pwm_range);

private:
    bool m_Forward = false;
    int m_DutyCycle = 0.0f;
    uint m_SliceNum;
};


#endif /* PICO_DC_MOTOR_H */
