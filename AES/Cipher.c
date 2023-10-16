#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint8_t* Cipher(uint8_t* in, uint8_t* key, int Nk){// here k is small letter
    //first i have do initial addroundkkey
    in = AddRoundKey(in);
    return ;
}