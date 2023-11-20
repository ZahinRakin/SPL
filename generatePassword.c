#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

char* randomLengthPass(char*);
char* customLengthPass(char*);

char* generatePassword(char* password){
  int choice;
  srand(time(NULL));
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