#include "header.h"
#include <stdio.h>

uint8_t* KeyExpansion(uint8_t* w){
    //adding the initial keys
    for(int i = 0; i < Nb; i++){
        *(w+1) = key[i];
    }
    return w;
}