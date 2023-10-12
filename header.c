#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include "header.h"
#define PRIME_UPTO 1000//up to ten thousand i don't get the segmentation fault. but at ten thousand i get arithmatic exception.
int primeNumbers[PRIME_UPTO];
int totalPrimeNumbers = 0;
void createAccount(){
  FILE* fp;
  int choice;
  char* password;
  char password_2[53];
  char username[20];
  
  printf("username:");
  scanf("%s",username);
  getchar();
  printf("\n\n");
  strcat(username,".txt");
  fp = fopen(username, "a+");
  if(fp == NULL){
    printf("Error while opening file.\n");
    exit(1);
  }

  printf("\033[0;37m1.Generate Password.\n\n2.Give Password.\033[0;31m(character:6-52)\n\n\033[0;37mChoice: \033[0m");
  scanf("%d",&choice);
  printf("\n\n");
  getchar();
  if(choice == 1){
    password = generatePassword(password);
    
    fprintf(fp,"%s\n",password);
  }
  else if(choice == 2){
    Again:
    printf("\033[0;32mPassword(length should be between 6 to 52): \033[0m");
    scanf("%s",password_2);
    printf("\n\n");
    if(strlen(password_2) < 6 || strlen(password_2) > 52){
      printf("\033[0;31mYou didn't follow the rule.\n\n\033[0m");
      goto Again;
    }
    int strength = checkStrength(password_2,strlen(password_2));
    if(strength == 0){
      goto Again;
    }
    else{
      fprintf(fp,"%s\n",password_2);
    }
  }
  else {
    printf("\x1b[31m");
    printf("Wrong command!\n");
    printf("\x1b[0m");
  }
  fclose(fp);//this should solve the problem number2: password at last ;(
  keyGenerate(username);
  
  main();
} 

void logIn(){
  FILE* fp;
  char username[80];
  char password[53];
  char line[55];
  char line_2[20];//here is the public key e;
  char line_3[45];//here is the public key n;
  char choice;
  int publicKey;
  int n;
  printf("\033[1;37musername: \033[0m");
  scanf("%s",username);
  getchar();
  printf("\n\n");
  strcat(username,".txt");
  printf("\033[1;31mpassword: \033[0m");
  scanf("%s",password);
  getchar();
  printf("\n\n");

  fp = fopen(username,"r");
  if(fp == NULL){
    printf("\033[1;31mYou don't have an account!\n\n\033[0m");
    main();
  }

  fgets(line, sizeof(line), fp);
  if(line == NULL){
    printf("\033[1;31mProblem occured while reading the first line\n\n\033[0m");
    exit(0);
  }
  removeNewLine(line,strlen(line));//this code block reads the password;

  fgets(line_2, sizeof(line_2), fp);
  if(line_2 == NULL){
    printf("\033[1;31mProblem occured while reading the second line.\n\n");
    exit(0);
  }
  removeNewLine(line_2,strlen(line_2));//this code block reads the public key (e);
  publicKey = parseInt(line_2,15,strlen(line_2)-1);

  fgets(line_3, sizeof(line_3), fp);
  if(line_3 == NULL){
    printf("\033[1;31mProblem occured while reading the third line.\n\n\033[0m");
    exit(0);
  }
  removeNewLine(line_3,strlen(line_3));//this code block reads the n
  n = parseInt(line_3,40,strlen(line_3)-1);

  if(strcmp(line,password)){
    printf("\x1b[31m");
    printf("Wrong password!\n");
    printf("\x1b[0m");
    main();
  }
  fclose(fp);

  printf("\033[1;37ma) Store Information.\n\nb) View Information.\033[1;32m\n\nchoice: ");
  scanf("%c",&choice);
  printf("\n\n\033[0m");
  if(choice == 'a'){
    int choice_2;
    storeInformation(username,publicKey,n);
  }
  else if(choice == 'b'){
    int choice_2;
    viewInformation(username, publicKey, n);
    
  }
  else{
    printf("\x1b[31m");
    printf("Wrong command.\n");
    printf("\x1b[0m");
  }
}

char* generatePassword(char* password){
  int choice;
  printf("\033[1;37mDo you want to determine the length of the password?\n\n1)\033[1;32mYes.\033[0m\n\n0)\033[0;31mNo.\033[0m\n\nchoice: ");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");
  if(choice == 1){
    password = customLengthPass(password);
  }
  else if(choice == 0){
    password = randomLengthPass(password);
  }
  else {
    printf("wrong command!\n");
  }
  return password;
}

int checkStrength(char* password,int length){
  int count = 0;
  if(length >= 8 && length < 10){
    count++;
  }
  else if(length >= 10 && length < 16){
    count += 2;
  }
  else{
    count += 3;
  }
  for(int i = 0; i < length; i++){
    if(((int)password[i] >= 33 && (int)password[i] <= 47) || ((int)password[i] >= 58 && (int)password[i] <= 64) || ((int)password[i] >= 91 && (int)password[i] <= 96) || ((int)password[i] >= 123 && (int)password[i] <= 126)){
      count++;
      break;
    }
  }
  for(int i = 0; i < length; i++){
    if((int)password[i] >= 48 && (int)password[i] <= 57){
      count++;
      break;
    }
  }
  for(int i = 0; i < length; i++){
    if((int)password[i] >= 65 && (int)password[i] <= 90){
      count++;
      break;
    }
  }
  for(int i = 0; i < length; i++){
    if((int)password[i] >= 97 && (int)password[i] <= 122){
      count++;
      break;
    }
  }
  if(count == 7){
    printf("\x1b[32m");
    printf("Strong\n");
    printf("\x1b[0m");
    return 2;
  }
  else if(count >= 5 && count < 7){
    printf("\x1b[33m");
    printf("medium\n");
    printf("\x1b[0m");
    return 1;
  }
  else if(count < 5){
    printf("\x1b[31m");
    printf("weak\n");
    printf("\x1b[0m");
    return 0;
  }
}

char* customLengthPass(char* password){
  int length, i;
  printf("\033[1;37mLength of your password \033[1;31m(length must be between 6 to 52):\033[0m ");
  scanf("%d",&length);
  printf("\n\n");
  length++;
  password = malloc((length)*sizeof(char));
  for(i = 0; i < length-1; i++){
    password[i] = (char)(rand()%93 + 33);
  }
  password[i] = '\0';
  return password;
}

char* randomLengthPass(char* password){
  int length, i;
  length = rand()%46 + 6;
  password = malloc(length*sizeof(char));
  for(i = 0; i < length-1; i++){
    password[i] = (char)(rand()%93 + 33);
  }
  password[i] = '\0';
  return password;  
}

int gcd(int n1, int n2){
  int gcd;
  for(int i = 1; i <= n1 && i <= n2; i++){
    if(n1%i == 0 && n2%i == 0){
      gcd = i;
    }
  }
  return gcd;
}

void primeNumberGenerator(){
  int arr[PRIME_UPTO];
  for(int i = 0; i < PRIME_UPTO; i++){
    arr[i] = 1;
  }
  arr[0] = 0;
  arr[1] = 0;
  for(int i = 2; i < PRIME_UPTO; i++){
    if(arr[i]){
      primeNumbers[totalPrimeNumbers++] = i;
      for(int j = i*i; j < PRIME_UPTO; j += i){
        arr[j] = 0;
      }
    }
  }
}

int pickRandomPrime(){
  int a = (int)rand()%totalPrimeNumbers;//here arithmatic exception occurs ;( line: 333(problem solved);
  for(int i = a; i < totalPrimeNumbers; i++){
    primeNumbers[i] = primeNumbers[i+1];
  }
  totalPrimeNumbers--;
  return primeNumbers[a];
}

void keyGenerate(char *username){
  FILE *fp;
  fp = fopen(username,"a");
  if(fp == NULL){
    printf("\033[1;31mERROR OCCURED WHILE OPENING THE FILE\033[0m\n\n");
    exit(0);
  }
  primeNumberGenerator();//this should solve the arithmatic exception problem.
  int p = pickRandomPrime();
  int q = pickRandomPrime();
  int phi = (p-1)*(q-1);
  int n = p*q;
  int e = 2;
  int d = 2;
  while(1){
    if(gcd(e,phi) == 1){
      break;
    }
    e++;
  }
  while(1){
    if((d*e)%phi == 1){
      break;
    }
    d++;
  }
  printf("\033[1;34m\nYOUR PRIVATE KEY: \033[1;37m%d\n\n\033[0m",d);
  fprintf(fp,"public key(e): %d\nMultiplication of two prime numbers(n): %d\n",e,n);
  fclose(fp);
}

void encoder(char* message, int* encoded, int publicKey, int n){
  for (int i = 0; message[i] != '\0'; i++) {
    encoded[i] = encrypt((int)message[i],publicKey,n);
  }
}

void decoder(int *encoded, char* decoded,int privateKey, int n){
  int i;
  for (i = 0; encoded[i] != '\0'; i++) {
    decoded[i] = (char)decrypt(encoded[i],privateKey, n);
  }
  decoded[i-3] = '\0';
}

int parseInt(char* str,int start, int end){
  int number = 0;
  for(int i = start ; i <= end; i++){
    number = number*10 + ((int)str[i] - '0');
  }
  return number;
}

long long int encrypt(double asciiValue, int e, int n){ //e = public key;
  long long int encodedChar = 1;
  while(e--){
    encodedChar *= asciiValue;
    encodedChar %= n;
  }
  return encodedChar;
}

long long int decrypt(int encodedChar,int d, int n){// d = private key;

  long long int decodedChar = 1;
  while(d--){
    decodedChar *= encodedChar;
    decodedChar %= n;
  }
  return decodedChar;
}

void removeNewLine(char* str, int size){
  if(size > 0 && str[size - 1] == '\n'){
    str[size-1] = '\0';
  }
}

void storeInformation(char* username, int publicKey, int n){
  FILE *fp;
  int choice;
  char *password;
  char password_2[53];
  char websiteAddress[100];
  char emailAddress[80];
  int choice_2;
  int *encodedMessage;

  fp = fopen(username,"a");
  if(fp == NULL){
    printf("\033[1;31mFILE CANN'T BE OPENED!\n\n\033[0m");
    exit(1);
  }

  printf("\033[1;37mWebsite Address: \033[0m");
  scanf("%s",websiteAddress);
  getchar();
  printf("\n\n");
  encodedMessage = malloc(sizeof(int)*strlen(websiteAddress));
  encoder(websiteAddress,encodedMessage,publicKey,n);//here i have modified;
  for(int i = 0; i < strlen(websiteAddress);i++){
    fprintf(fp,"%d",encodedMessage[i]);
  }
  fprintf(fp,"\n");
  free(encodedMessage);

  printf("\033[1;37mEmail Address: \033[0m");
  scanf("%s",emailAddress);
  getchar();
  printf("\n\n");
  encodedMessage = malloc(sizeof(int)*strlen(emailAddress));
  encoder(emailAddress,encodedMessage,publicKey,n);//modified.
  for(int i = 0; i < strlen(emailAddress);i++){
    fprintf(fp,"%d",encodedMessage[i]);
  }
  fprintf(fp,"\n");
  free(encodedMessage);

  printf("\033[1;37m1) Generate Password.\n\n2) Give password.\n\n\033[1;32mchoice: \033[0m");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");

  if(choice == 1){
    password = generatePassword(password);
    encodedMessage = malloc(sizeof(int)*strlen(password));
    encoder(password,encodedMessage,publicKey,n);//
    for(int i = 0; i < strlen(password);i++){
      fprintf(fp,"%d",encodedMessage[i]);
    }
    fprintf(fp,"\n");
    free(encodedMessage);
  }
  else if(choice == 2){
    again:
    printf("\033[1;31mRemember to keep password within 6-52 character:\033[0m ");
    scanf("%s",password_2);
    printf("\n\n");
    if(strlen(password_2) < 6 || strlen(password_2) > 52){
      printf("\033[1;31mYOUR PASSWORD LENGTH ISN'T WITHING 6-52.\n\n\033[0m");
      goto again;
    }
    getchar();
    int strength = checkStrength(password_2,strlen(password_2));

    if(!strength){
      goto again;
    }
    else{
      encodedMessage = malloc(sizeof(int)*strlen(password_2));
      encoder(password_2,encodedMessage,publicKey,n);//
      for(int i = 0; i < strlen(password_2);i++){
        fprintf(fp,"%d",encodedMessage[i]);
      }
      fprintf(fp,"\n");
      free(encodedMessage);
    }
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
    exit(1);
  }
  fclose(fp);
  printf("\033[1;32mWhat do you want to do now?\033[0;37m\n\n");
  printf("0)Store more information.\n\n1) Return home.\n\n2) View your information.\n\n\033[1;31m3) exit.\n\n\033[0;32mchoice: \033[0m");
  scanf("%d",&choice_2);
  getchar();
  printf("\n\n");

  if(choice_2 == 0){
    storeInformation(username,publicKey,n);//modified
  }
  else if(choice_2 == 1){
    main();
  }
  else if(choice_2 == 2){
    viewInformation(username,publicKey,n);//modified
  }
  else if(choice_2 == 3){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}

void viewInformation(char* username,int publicKey, int n){
  FILE *fp;
  int choice_2;
  int lineNumber = 0;
  int encodedMessage[10000];//3 octobar 2023.
  int privateKey;
  printf("\033[1;31mWhat is you private key?\n\nKEY: \033[0m");
  scanf("%d",&privateKey);
  printf("\n\n");
  printf("\033[1;34mAll the information of this user: %s\n\n\033[0m",username);
  
  char line[1000];
  fp = fopen(username,"r");
  if(fp == NULL){
    printf("\033[1;31mCANN'T OPEN THE FILE!\n\n\033[0m");
    exit(1);
  }
  while(fgets(line,sizeof(line),fp)){
    if(lineNumber >= 3){
      removeNewLine(line,strlen(line));
      //encodedMessage = malloc(strlen(line)*sizeof(int));
      for(int i = 0; i < strlen(line); i++){
        encodedMessage[i] = (int)line[i];
      }
      decoder(encodedMessage,line,privateKey,n);//it wasn't working before because of passing value problem. but i corrected it still it isn't working i think there is a problem with the key generation.
      printf("%s\n",line);
    }
    else{
      removeNewLine(line,strlen(line));
      printf("%s\n",line);
    }
    lineNumber++;
  }
  
  fclose(fp);
  printf("\033[1;31m\n\nWHAT DO YOU WANT TO DO NOW?\n\n\033[0m");
  printf("\033[1;37m1) Return home.\n\n2) Store information.\n\n\033[1;31m3) exit.\n\n\033[0;32mchoice: ");
  scanf("%d",&choice_2);
  getchar();
  printf("\n\n");

  if(choice_2 == 1){
    main();
  }
  else if(choice_2 == 2){
    storeInformation(username,publicKey,n);//modified
  }
  else if(choice_2 == 3){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}