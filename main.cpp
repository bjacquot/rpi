#include <QCoreApplication>
#include "io/pwm.h"
#include "io/pwmclk.h"

int main(int argc, char *argv[])
{
    PwmClk *pwmConf= new PwmClk();
    pwmConf->setPwmClkDiv(32);
    Pwm *moteurG=new Pwm(0);
    Pwm *moteurD=new Pwm(1);

    moteurD->setRange(2000);
    moteurG->setRange(2000);

    moteurD->setRapportCyclique(1500);
    moteurG->setRapportCyclique(500);

    return 0;

}
