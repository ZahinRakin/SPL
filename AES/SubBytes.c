#include <stdio.h>
#include "header.h"

uint8_t* SubBytes(uint8_t* state){
    for(int i = 0; i < 16; i++){
        *(state+i) = S_BOX[*(state+i)];
    }
    return state;
}