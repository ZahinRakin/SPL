#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main();
void createAccount();
void logIn();
int checkStrength(char *, int);
char *generatePassword(char *);
char *customLengthPass(char *);
char *randomLengthPass(char *);
void removeNewLine(char *, int);
void storeInformation(char *);
void viewInformation(char *);
void updatePassword(char *);
void upload(char *);
// methods for aes.
#define AES_BLOCK_SIZE 16
#define AES_ROUNDS 10
#define AES_ROUND_KEY_SIZE 176

void stringToHex(char *, unsigned char *);
void hexToString(unsigned char *, char *);
unsigned char *cipher(char *, unsigned char *);
unsigned char *invCipher(unsigned char *, unsigned char *); // there could be problem...

void subBytes(unsigned char *);
void addRoundKey(unsigned char *, unsigned char *, int *);
void shiftRows(unsigned char *);
void mixColumns(unsigned char *);
void keyExpansion(unsigned char *, unsigned char *);
void aesEncrypt(unsigned char *, unsigned char *);
void stringToBytes(unsigned char *, unsigned char *);
void bytesToString(unsigned char *, char *);
// decrypt methods.
void aesDecrypt(unsigned char *, unsigned char *);
void invShiftRows(unsigned char *);
void invSubBytes(unsigned char *);
void invMixColumns(unsigned char *);
int padding(char *); // returns the length of padding.

extern unsigned char key[];
extern unsigned char SBOX[256];
extern unsigned char INV_SBOX[256];

extern unsigned char RC[];
// end...
// methods for rsa
#define MAX 10000
extern int primeNumbers[MAX];
extern long numberOfPrimeNumbers;
void primeFiller();
long pickRandomPrime();
double SQRT(double);
void keyGenerator();
long gcd(long, long);
long encrypt(int, long, long);
void encoder(char *, long *, long, long);
int decrypt(long, long, long);
void decoder(long *, int, char *, long, long);
// end...
// socket methods
void download();
void uploadToServer(char *);

#endif
