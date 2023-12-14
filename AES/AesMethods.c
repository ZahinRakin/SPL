#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void addRoundKey(unsigned char* state,unsigned char* roundkeys, int* count){
    roundkeys += *count;
    for (int i = 0; i < AES_BLOCK_SIZE; ++i ) {
        *(state+i) ^= *roundkeys++;
        (*count)++;
    }
}

void subBytes(unsigned char* state){
    for(int i = 0; i < 16; i++){
        *(state+i) = SBOX[*(state+i)];
    }
}

void shiftRows(unsigned char* state){
    //there is no change for row 0;
    //row = 1;
    unsigned char temp = *(state+1);
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
}

static unsigned char galoisMultiply(unsigned char a, unsigned char b){//this method is needed in mix columns.
    unsigned char p = 0;
    int i;
    int carry;
    for(i = 0; i < 8; i++){
        if((b & 1) == 1){
            p ^= a;
        }
        b >>= 1;
        carry = a & 0x80;
        a <<= 1;
        if(carry == 0x80){
            a ^= 0x1b;
        }
    }
    return p;
}

void mixColumns(unsigned char* input){
    unsigned char* state = (unsigned char*)malloc(sizeof(unsigned char) * 16);
    for(int i = 0; i < 16; i++)
        state[i] = input[i];
    int c;
    for(c = 0; c < 4; c++){
        *(input++) = galoisMultiply(*(state++), 2) ^ galoisMultiply(*(state++), 3) ^ *(state++) ^ *(state++); state -= 4;
        *(input++) = *(state++) ^ galoisMultiply((*state++), 2) ^ galoisMultiply(*(state++), 3) ^ *(state++); state -= 4;
        *(input++) = *(state++) ^ *(state++) ^ galoisMultiply(*(state++), 2) ^ galoisMultiply(*(state++), 3); state -= 4;
        *(input++) = galoisMultiply(*(state++), 3) ^ *(state++) ^ *(state++) ^ galoisMultiply(*(state++), 2);
    }
}

void keyExpansion(unsigned char *key, unsigned char *roundkeys) {
    unsigned char temp[4];//it contain one word
    unsigned char *last4bytes; // last word of a round
    unsigned char *lastround;//points to the first byte of the first element
    unsigned char i;

    for (i = 0; i < 16; i++) {
        *roundkeys++ = *key++;//this works if both of them are arrays at root. i mean when declared. if one of them is pointer and then memory allocated it won't work.
    }

    last4bytes = roundkeys-4;
    for (i = 0; i < AES_ROUNDS; ++i) {
        // k0-k3 for next round
        temp[3] = SBOX[*last4bytes++];
        temp[0] = SBOX[*last4bytes++];
        temp[1] = SBOX[*last4bytes++];
        temp[2] = SBOX[*last4bytes++];
        temp[0] ^= RC[i];// rotword + subword + rcondition
        lastround = roundkeys-16;//there could be problem with this or not. probably not.
        *roundkeys++ = temp[0] ^ *lastround++;
        *roundkeys++ = temp[1] ^ *lastround++;
        *roundkeys++ = temp[2] ^ *lastround++;
        *roundkeys++ = temp[3] ^ *lastround++;//first word of the next batch.
        // k4-k7 for next round        
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        // k8-k11 for next round
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        // k12-k15 for next round
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
        *roundkeys++ = *last4bytes++ ^ *lastround++;
    }
}

void invShiftRows(unsigned char* state){
    unsigned char temp;
    // row1
    temp        = *(state+13);
    *(state+13) = *(state+9);
    *(state+9)  = *(state+5);
    *(state+5)  = *(state+1);
    *(state+1)  = temp;
    // row2
    temp        = *(state+14);
    *(state+14) = *(state+6);
    *(state+6)  = temp;
    temp        = *(state+10);
    *(state+10) = *(state+2);
    *(state+2)  = temp;
    // row3
    temp        = *(state+3);
    *(state+3)  = *(state+7);
    *(state+7)  = *(state+11);
    *(state+11) = *(state+15);
    *(state+15) = temp;
}

void invSubBytes(unsigned char* state){
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        *(state+i) = INV_SBOX[*(state+i)];
    }
}

void invMixColumns(unsigned char* input){
    unsigned char* state = (unsigned char*)malloc(sizeof(unsigned char) * 16);
    for(int i = 0; i < 16; i++)
        state[i] = input[i];
    int c;
    for(c = 0; c < 4; c++){
        *(input++) = galoisMultiply(*(state++), 14) ^ galoisMultiply(*(state++), 11) ^ galoisMultiply(*(state++), 13) ^ galoisMultiply(*(state++), 9); state -= 4;
        *(input++) = galoisMultiply(*(state++), 9) ^ galoisMultiply((*state++), 14) ^ galoisMultiply(*(state++), 11) ^ galoisMultiply(*(state++), 13); state -= 4;
        *(input++) = galoisMultiply(*(state++), 13) ^ galoisMultiply(*(state++), 9) ^ galoisMultiply(*(state++), 14) ^ galoisMultiply(*(state++), 11); state -= 4;
        *(input++) = galoisMultiply(*(state++), 11) ^ galoisMultiply(*(state++), 13) ^ galoisMultiply(*(state++), 9) ^ galoisMultiply(*(state++), 14);
    }
}

void aesEncrypt(unsigned char* state, unsigned char* roundKeys){
    static int count = 0;
    addRoundKey(state,roundKeys, &count);

    for(int i = 1; i < AES_ROUNDS; i++){
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state,roundKeys, &count);
    }

    subBytes(state);
    shiftRows(state);
    addRoundKey(state,roundKeys, &count);
    count = 0;
}

void aesDecrypt(unsigned char* state, unsigned char* roundKeys){
    int count;
    count = AES_ROUND_KEY_SIZE - 16;
    addRoundKey(state, roundKeys, &count);
    for(int i = AES_ROUNDS - 1; i >= 1; i--){
        invShiftRows(state);
        invSubBytes(state);
        count = i*AES_BLOCK_SIZE;
        addRoundKey(state, roundKeys, &count);
        invMixColumns(state);
    }
    invShiftRows(state);
    invSubBytes(state);
    count = 0;
    addRoundKey(state, roundKeys, &count);
    count = AES_ROUND_KEY_SIZE - 16;
}

unsigned char* cipher(char* input, unsigned char* output, unsigned char* key) {
    if(input[strlen(input)-1] == '\n'){
        input[strlen(input)-1] = '\0';
    }
	int length = strlen(input);
	unsigned char padd[16];
	unsigned char* state;
    int i;
	int paddLength = 16 - length % 16;
    for(i = 0; i < paddLength; i++){
        padd[i] = ' ';
    }
	padd[i] = '\0';
	strcat(input,padd);

	output = malloc(sizeof(unsigned char)*strlen(input));
	unsigned char hexString[strlen(input)*2 + 1];
	stringToHex(input, hexString);
	stringToBytes(hexString, hexString);//string to bytes done
	
	unsigned char roundkeys[AES_ROUND_KEY_SIZE];
	keyExpansion(key, roundkeys);//key expansion done.

	i = 0;
	while(i < (length + paddLength)){
		state = malloc(sizeof(unsigned char)*16);
		for(int j = 0; j < 16; j++){
			state[j] = hexString[i + j];
		}
		aesEncrypt(state,roundkeys);
		for(int j = 0; j < 16; j++){
			output[i + j] = state[j];
		}
		i += 16;
		free(state);
	}
	
    return output;
} 

unsigned char* invCipher(unsigned char* input, unsigned char* output, unsigned char* key) {
    if(input[strlen(input)-1] == '\n'){
        input[strlen(input)-1] = '\0';
    }
	int length = strlen(input)/2;
	output = malloc(sizeof(unsigned char)*length);
	stringToBytes(input, output);
	unsigned char* state;
    int i;    
	unsigned char roundkeys[AES_ROUND_KEY_SIZE];
	keyExpansion(key, roundkeys);

	i = 0;
	while(i < length){
		state = malloc(sizeof(unsigned char)*16);
		for(int j = 0; j < 16; j++){
			state[j] = output[i + j];
		}
		aesDecrypt(state,roundkeys);
		for(int j = 0; j < 16; j++){
			output[i + j] = state[j];
		}
		i += 16;
		free(state);
	}
	return output;
} 

void stringToHex(char* input,unsigned char* output) {
    int length = strlen(input);
    int outputIndex = 0;

    for (int i = 0; i < length; ++i) {
        sprintf(output + outputIndex, "%02x", input[i]);
        outputIndex += 2;
    }
    output[outputIndex] = '\0';
}
//it works when the hex string is string not an actual array.
void hexToString(unsigned char hexString[], char charString[]) {
    int hexStringLength = strlen(hexString);
    if (hexStringLength % 2 != 0) {
        printf("Error: Hex string length must be even.\n");
        exit(1);
    }
    for (int i = 0; i < hexStringLength; i += 2) {
        sscanf(hexString + i, "%2hhx", &charString[i / 2]);
    }
    charString[hexStringLength / 2] = '\0';
}

void stringToBytes(unsigned char* str, unsigned char* bytes){
    int i;
    for(i = 0; i < strlen(str) - 1; i += 2){
        char* pair = malloc(2 * sizeof(char));
        memcpy(pair, &str[i], 2);
        bytes[i/2] = strtol(pair, NULL, 16);
        free(pair);
    }
}

void bytesToString(unsigned char* input, char* output){
    int size = strlen(input);
    char *ptr = &output[0];

    int i;

    for (int i = 0; i < size; i++) {
        ptr += sprintf(ptr, "%02x", input[i]);
    }
}

int padding(char* input){
  int length = strlen(input);
	unsigned char padd[16];
  int i;
	int paddLength = 16 - length % 16;
  for(i = 0; i < paddLength; i++){
      padd[i] = ' ';
  }
	padd[i] = '\0';
	strcat(input,padd);//padding done
    return paddLength;
}

void purifyKey(unsigned char* input){
    int paddlength = padding(input);
    unsigned char hexString[strlen(input)*2 + 1];
	stringToHex(input, hexString);
	stringToBytes(hexString, input);//string to bytes done
}