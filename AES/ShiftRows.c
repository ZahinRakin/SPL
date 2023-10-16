#include <stdio.h>
#include "header.h"

uint8_t* ShiftRows(uint8_t* state){
    //there is no change for row 0;
    //row = 1;
    uint8_t temp = *(state+1);
    *(state+1) = *(state+5);
    *(state+5) = *(state+9);
    *(state+9) = *(state+13);
    *(state+13) = temp;
    //row = 2;
    temp = *(state+2);
    *(state+2) = *(state+10);
    *(state+10) = temp;
    temp = *(state+6);
    *(state+6) = *(state+14);
    *(state+14) = temp;
    //row = 3
    temp = *(state+3);
    *(state+3) = *(state+15);
    *(state+15) = *(state+11);
    *(state+11) = *(state+7);
    *(state+7) = temp;

    return state;
}