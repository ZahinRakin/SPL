#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

uint8_t* Cipher(uint8_t* in, uint8_t* key, int Nk){// here k is small letter
    uint8_t* state = in;
    uint8_t* w = KeyExpansion(w);
    //Initial transformation
    state = AddRoundKey(state,w);

    for(int i = 1; i < Nr; i++){
        state = SubBytes(state);
        state = ShiftRows(state);
        state = MixCollumns(state);
        state = AddRoundKey(state,w);
    }

    state = SubBytes(state);
    state = ShiftRows(state);
    state = AddRoundKey(state,w);

    return state;
}