#ifndef HEADER_H
#define HEADER_H
void createAccount();
void logIn();
int checkStrength(char*, int);
char* generatePassword(char*);
char* customLengthPass(char*);
char* randomLengthPass(char*);


//encryption algorithm's method.
int gcd(int, int);
void primeNumberGenerator();
int pickRandomPrime();
void keyGenerate(char*);
long long int encrypt(double, int, int);
long long int decrypt(int, int, int);
void encoder(char*, int*, int, int);
void decoder(int*, char*, int, int);
int parseInt(char* ,int, int);



void removeNewLine(char*, int);
void storeInformation(char*, int, int);
void viewInformation(char*, int, int);

#endif