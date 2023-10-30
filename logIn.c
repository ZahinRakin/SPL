#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void logIn(){
  FILE* fp;
  char username[80];
  char password[53];
  char line[55];
  char choice;


  again:
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
  fclose(fp);

  if(line == NULL){
    printf("\033[1;31mProblem occured while reading the first line\n\n\033[0m");
    exit(0);
  }
  removeNewLine(line,strlen(line));//this code block reads the password;

  if(strcmp(line,password)){
    printf("\x1b[31m");
    printf("Wrong password!\n");
    printf("\x1b[0m");
    goto again;
  }
  

  printf("\033[1;37ma) Store Information.\n\nb) View Information.\033[1;32m\n\nc) Update information\n\nchoice: ");
  scanf("%c",&choice);
  printf("\n\n\033[0m");
  if(choice == 'a'){
    storeInformation(username);
  }
  else if(choice == 'b'){
    viewInformation(username);
  }
  else if(choice == 'c'){
    updatePassword(username);
  }
  else{
    printf("\x1b[31m");
    printf("Wrong command.\n");
    printf("\x1b[0m");
  }
}