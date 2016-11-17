#include "pwm.h"
#include <iostream>
#include <unistd.h>
using namespace std;

#define PWM_CTL_PWM0 0
#define PWM_CTL_PWM1 8
#define GPIO_FSEL12 6
#define GPIO_FSEL13 9

#define PWM_MODE_NORMAL 0x1

Pwm::Pwm(unsigned int pwmNumber):RpiPeripherique()
{
    int offset,offsetGPIO;
    if (pwmNumber>1)
    {
        cout << "le numéro de PWM doit être 0 ou 1 !"<<endl;
        exit(-1);
    }
    if (pwmNumber==0)
    {
        cout <<"pwm0"<<endl;
        regPWM_RNG = regPWM_RNG0;
        regPWM_DAT = regPWM_DAT0;
        offset = PWM_CTL_PWM0;
        offsetGPIO = GPIO_FSEL12;
    }
    else
    {
        cout <<"pwm1"<<endl;
        regPWM_RNG = regPWM_RNG1;
        regPWM_DAT = regPWM_DAT1;
        offset = PWM_CTL_PWM1;
        offsetGPIO = GPIO_FSEL13;
    }
    regClearBits(regPWM_CTL,0xff,offset);
    regClearBits(regGPIO_FSEL,0x7,offsetGPIO);
    regSetBits(regGPIO_FSEL,0x4,offsetGPIO);
    usleep(110);
    regSetBits(regPWM_CTL,PWM_MODE_NORMAL,offset);

}

void Pwm::setRange(unsigned int rng)
{
    mRange = rng;
    regWrite(regPWM_RNG,rng);
    setRapportCyclique(0);
}

void Pwm::setRapportCyclique(unsigned int rapport)
{
    if (rapport > mRange)
    {
        cout << "rapport cyclique non adapté !"<<mRange<<" "<<rapport<<endl;
        exit(-1);
    }
    mRapportCyclique = rapport;
    regWrite(regPWM_DAT,rapport);
}
