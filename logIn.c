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
  printf("\033[1;37mUSERNAME: \033[0m");
  scanf("%s",username);
  getchar();
  printf("\n");
  strcat(username,".txt");

  printf("\033[1;31mPASSWORD: \033[0m");
  scanf("%s",password);
  getchar();
  printf("\n");

  fp = fopen(username,"r");
  if(fp == NULL){
    printf("\033[1;31mNO ACCOUNT FOUND!\n\n\033[0m");
    goto again;
  }

  //READING THE PASSWORD FROM THE FILE.
  fgets(line, sizeof(line), fp);
  fclose(fp);
  if(line == NULL){
    printf("\033[1;31mPROBLEM OCCURED WHILE READING THE FIRST LINE!\n\n\033[0m");
    exit(0);
  }
  removeNewLine(line,strlen(line));


  if(strcmp(line,password)){
    printf("\033[1;31mWRONG PASSWORD!\n\n");
    goto again;
  }

  printf("\033[1;37m");
  printf("a) STORE INFORMATION.\n\n");
  printf("b) VIEW INFORMATION.\n\n");
  printf("c) EXIT.\n\n");
  printf("CHOICE: \033[0m");
  scanf("%c",&choice);


  if(choice == 'a'){
    storeInformation(username);
  }
  else if(choice == 'b'){
    viewInformation(username);
  }
  else if(choice == 'c'){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}
