#ifndef PWM_H
#define PWM_H
#include "rpiperipherique.h"

class Pwm : public RpiPeripherique
{
private:
    unsigned int mRange=0;
    unsigned int mRapportCyclique=0;
    const unsigned int regGPIO_FSEL = 0x200004; // Clock controller
    const unsigned int regPWM_CTL   = 0x20C000; // Clock controller
    const unsigned int regPWM_RNG0  = 0x20C010; // Clock controller
    const unsigned int regPWM_DAT0  = 0x20C014; // Clock controller
    const unsigned int regPWM_RNG1  = 0x20C020; // Clock controller
    const unsigned int regPWM_DAT1  = 0x20C024; // Clock controller
    unsigned int regPWM_RNG; // Clock controller
    unsigned int regPWM_DAT; // Clock controller

public:
    Pwm(unsigned int pwmNumber);
    void setRange(unsigned int rng);
    void setRapportCyclique(unsigned int rapport);
};

#endif // PWM_H
