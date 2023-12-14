#ifndef HEADER_H
#define HEADER_H

#define AES_BLOCK_SIZE      16
#define AES_ROUNDS          10
#define AES_ROUND_KEY_SIZE  176 

void stringToHex(char*, unsigned char*);
void hexToString(unsigned char[], char[]);
unsigned char* cipher(char*, unsigned char*, unsigned char*);
unsigned char* invCipher(unsigned char*, unsigned char*, unsigned char*);//there could be problem...

void subBytes(unsigned char*);
void addRoundKey(unsigned char*, unsigned char*, int*);
void shiftRows(unsigned char*);
void mixColumns(unsigned char*);
void keyExpansion(unsigned char*,unsigned char*);
void aesEncrypt(unsigned char*, unsigned char*);
void stringToBytes(unsigned char*, unsigned char*);
void bytesToString(unsigned char*, char*);
//decrypt methods.
void aesDecrypt(unsigned char*, unsigned char*);
void invShiftRows(unsigned char*);
void invSubBytes(unsigned char*);
void invMixColumns(unsigned char*);
int padding(char*);
void purifyKey(unsigned char*);

extern unsigned char key[];
extern unsigned char SBOX[256];
extern unsigned char INV_SBOX[256];

extern unsigned char RC[];


#endif