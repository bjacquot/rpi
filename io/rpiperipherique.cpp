#include "rpiperipherique.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

RpiPeripherique::RpiPeripherique()
{
    uint8_t buf[4];
    int memSize = 0;
    int fd = open("/sys/firmware/devicetree/base/soc/ranges", O_RDONLY);
    if (fd<=0)
    {
        cout << "Pb de configuration de sysfs !!"<<endl;
        exit(-1);
    }
    lseek(fd, 4, SEEK_SET);
    if (read(fd, buf, sizeof(buf)) == sizeof(buf)) {
        mBaseAdress = (buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] );
        cout << "Adresse de base des périphs : 0x"<< hex << mBaseAdress <<endl;
    }
    lseek(fd, 8, SEEK_SET);
    if (read(fd, buf, sizeof(buf)) == sizeof(buf)) {
        memSize = (buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] );
        cout << "Taille de la mémoire : 0x"<< hex << memSize <<endl;
    }
    close(fd);
    if ( (memSize==0) || (mBaseAdress==0) )
    {
        cout << "Pb de lecture des paramètres mémoire !!"<<endl;
        exit(-1);
    }
    fd = open("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC);
    if (fd<=0)
    {
        cout << "Pb d'accès à /dev/mem !!"<<endl;
        exit(-1);
    }
    memMap = (unsigned int *)mmap(NULL, memSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, mBaseAdress);
    if (memMap == MAP_FAILED)
    {
        cout << "Pb de mappage mémoire !!"<<endl;
        exit(-1);
    }
    close(fd);
}

void RpiPeripherique::regWrite(unsigned int reg, unsigned int val)
{
    *(memMap+reg/4) = val;
}

void RpiPeripherique::regSetBits(unsigned int reg, unsigned int val, unsigned int offset)
{
    unsigned int regVal = *(memMap+reg/4);
    regVal |= val<<offset;
    *(memMap+reg/4) = regVal;
}

void RpiPeripherique::regClearBits(unsigned int reg, unsigned int val, unsigned int offset)
{
    unsigned int regVal = *(memMap+reg/4);
    regVal &=~ (val<<offset);
    *(memMap+reg/4) = regVal;
}

unsigned int RpiPeripherique::regRead(unsigned int reg)
{
    return *(memMap+reg/4);
}

