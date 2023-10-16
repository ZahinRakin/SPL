#include <stdio.h>
#include "header.h"

uint8_t mul2(uint8_t);

uint8_t* MixCollumns(uint8_t* state){
    for(int i = 0; i < Nk; i+= 4){
        uint8_t temp = state[i]^state[i+1]^state[i+2]^state[i+3];
        state[i]   = mul2(state[i]   ^ state[i+1]) ^ state[i]   ^ temp;
        state[i+1] = mul2(state[i+1] ^ state[i+2]) ^ state[i+1] ^ temp;
        state[i+2] = mul2(state[i+2] ^ state[i+3]) ^ state[i+2] ^ temp;
        state[i+3] = mul2(state[i+3] ^ state[i]  ) ^ state[i+3] ^ temp;
    }
    return state;
}

uint8_t mul2(uint8_t a){
    return (a & 0x80) ? ((a<<1)^0x1b) : (a<<1);
}