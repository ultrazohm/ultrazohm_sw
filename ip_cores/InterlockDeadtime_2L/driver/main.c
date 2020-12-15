#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "InterlockDeadtime_hw.h"
#include "InterlockDeadtime.h"

InterlockDeadtime_hw InterDeadHW;
InterlockDeadtime InterDead;

int main(void){

    printf("Start of test program\n");
    InterlockDeadtime_hw_init(&InterDeadHW, 1, 0x00001); // You can use the HW struct directly
    InterDeadHW.WriteResetIPCore(&InterDeadHW,true);
    InterDeadHW.WriteDelayCycles(&InterDeadHW,10);
    InterDeadHW.WriteEnableOutput(&InterDeadHW,true);
    InterDeadHW.WriteInverseBotSwitch(&InterDeadHW,false);
    InterDeadHW.WriteEnableIPCore(&InterDeadHW,true);

    InterlockDeadtime_init(&InterDead,2,0x00001,100,false,1.0);
    InterDead.SetDeadtimeInMicroseconds(&InterDead,2.0);

    uint32_t test;
    bool test2=false;
    bool booltest=true;
    test=(uint32_t)booltest; // type test,x in expressions to see as hex
    test2=(bool)test;
    return 0;
}