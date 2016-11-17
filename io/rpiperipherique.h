#ifndef RPIPERIPHERIQUE_H
#define RPIPERIPHERIQUE_H

#include <cstdint>

class RpiPeripherique
{
private:
    int mBaseAdress = 0;
    unsigned int *memMap;


public:
    RpiPeripherique();
protected :
    void regWrite(unsigned int reg, unsigned int val);
    void regSetBits(unsigned int reg, unsigned int val,unsigned int offset);
    void regClearBits(unsigned int reg, unsigned int val,unsigned int offset);
    unsigned int regRead(unsigned int reg);
};

#endif // RPIPERIPHERIQUE_H
