#ifndef PWMCLK_H
#define PWMCLK_H

#include "rpiperipherique.h"
/*
0     0 Hz     Ground
1     19.2 MHz oscillator
2     0 Hz     testdebug0
3     0 Hz     testdebug1
4     0 Hz     PLLA
5     1000 MHz PLLC (changes with overclock settings)
6     500 MHz  PLLD
7     216 MHz  HDMI auxiliary
8-15  0 Hz     Ground
*/

enum PwmMode {pwmNormal,pwmReparti};

class PwmClk : public RpiPeripherique
{
private:
    const unsigned int regCM_PWMCTL  = 0x1010a0; // Clock controller
    const unsigned int regCM_PWMDIV  = 0x1010a4; // Clock controller
    volatile unsigned int *clkReg;
    unsigned pwmPrediv = 0;

    void stopPwmClk();
    void startPwmClk();
    void regSetBitsWithPassword(unsigned int reg, unsigned int val,unsigned int offset);
    void regClearBitsWithPassword(unsigned int reg, unsigned int val,unsigned int offset);
public:
    PwmClk();
    void setPwmClkDiv(unsigned int prediv);
};

#endif // PWMCLK_H
