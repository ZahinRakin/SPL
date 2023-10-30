#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void viewInformation(char* username){
  FILE *fp;
  int choice;
  int lineNumber = 1;
  char line[100];

  printf("\033[1;34mAll the information of this user: %s\n\n\033[0m",username);
  

  fp = fopen(username,"r");
  if(fp == NULL){
    printf("\033[1;31mCANN'T OPEN THE FILE!\n\n\033[0m");
    exit(1);
  }
  while(fgets(line,sizeof(line),fp)){
    if(lineNumber > 1){
      printf("%s",line);
    }
    lineNumber++;
  }
  
  fclose(fp);


  printf("\033[1;31m\n\nWHAT DO YOU WANT TO DO NOW?\n\n\033[0m");
  printf("\033[1;37m1) Return home.\n\n2) Store information.\n\n\033[1;31m3) exit.\n\n\033[0;32mchoice: ");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");

  if(choice == 1){
    main();
  }
  else if(choice == 2){
    storeInformation(username);
  }
  else if(choice == 3){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}