#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

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


  printf("\033[0;37m1.Generate Password.\n\n2.Give Password.\033[0;31m(character:6-52)\n\n\033[0;37mChoice: \033[0m");
  scanf("%d",&choice);
  printf("\n\n");
  getchar();


  if(choice == 1){
    password = generatePassword(password);
    fp = fopen(username, "a");
    if(fp == NULL){
      printf("Error while opening file.\n");
      exit(1);
    }
    fprintf(fp,"%s\n",password);
    fclose(fp);
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
      fp = fopen(username, "a");
      if(fp == NULL){
        printf("Error while opening file.\n");
        exit(1);
      }
      fprintf(fp,"%s\n",password_2);
      fclose(fp);
    }
  }
  else {
    printf("\x1b[31m");
    printf("Wrong command!\n");
    printf("\x1b[0m");
  }
  main();
} 