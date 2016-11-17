#include "pwmclk.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
using namespace std;

#define CM_PWMCTL_SRV 0
#define CM_PWMCTL_ENAB 4
#define CM_PWMCTL_KILL 5
#define CM_PWMCTL_BUSY 7
#define CM_PWMCTL_FLIP 8
#define CM_PWMCTL_MASH 9
#define CM_PWMCTL_PASSWORD 24

#define CM_PWMDIV_DIVF 0
#define CM_PWMDIV_DIVI 12

#define PWMCLK_PASSWORD 0x5a


PwmClk::PwmClk():RpiPeripherique()
{
    cout << "Horloge par défaut : clk1 19.2M"<<endl;
    cout << "MASH = 0 : % entiere"<<endl;
    stopPwmClk();
    regSetBitsWithPassword(regCM_PWMCTL,1,CM_PWMCTL_SRV);
    regClearBitsWithPassword(regCM_PWMCTL,3,CM_PWMCTL_MASH);
}

void PwmClk::regSetBitsWithPassword(unsigned int reg, unsigned int val, unsigned int offset)
{
    unsigned int regVal = regRead(reg);
    regVal |= (val<<offset)|(PWMCLK_PASSWORD<<CM_PWMCTL_PASSWORD);
    regWrite(reg,regVal);
}

void PwmClk::regClearBitsWithPassword(unsigned int reg, unsigned int val, unsigned int offset)
{
    unsigned int regVal = regRead(reg);
    regVal &=~(val<<offset);
    regVal |= PWMCLK_PASSWORD<<CM_PWMCTL_PASSWORD;
    regWrite(reg,regVal);
}

void PwmClk::stopPwmClk()
{
    cout << "Arret de l'horloge PWM ..."<<endl;
    regClearBitsWithPassword(regCM_PWMCTL,1,CM_PWMCTL_ENAB);
    while (regRead(regCM_PWMCTL)&(1<<CM_PWMCTL_BUSY));
    cout <<"ok"<<endl;
}

void PwmClk::startPwmClk()
{
    cout <<"Démarrage de l'horloge PWM ..."<<endl;
    regSetBitsWithPassword(regCM_PWMCTL,1,CM_PWMCTL_ENAB);
    while ( (regRead(regCM_PWMCTL)&(1<<CM_PWMCTL_BUSY)) == 0);
    cout << "ok !"<<endl;
}

void PwmClk::setPwmClkDiv(unsigned int prediv)
{
    if (prediv > 0xfff)
    {
        cout <<"prediviseur trop grand !!"<<endl;
        exit(-1);
    }
    stopPwmClk();
    regClearBitsWithPassword(regCM_PWMDIV,0xfff,CM_PWMDIV_DIVI);
    regSetBitsWithPassword(regCM_PWMDIV,prediv,CM_PWMDIV_DIVI);
    startPwmClk();
}

