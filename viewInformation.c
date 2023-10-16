#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void viewInformation(char* username){
  FILE *fp;
  int choice;
  int lineNumber = 0;
  char line[1000];

  printf("\033[1;34mALL THE INFORMATION ABOUT THIS USER: %s\n\n\033[0m",username);
  
  fp = fopen(username,"r");
  if(fp == NULL){
    printf("\033[1;31mCANN'T OPEN THE FILE!\n\n\033[0m");
    exit(1);
  }
  
  while(fgets(line,sizeof(line),fp)){
    if(lineNumber >= 1){
      removeNewLine(line,strlen(line));
      printf("%s\n",line);
    }
    lineNumber++;
  }
  
  fclose(fp);
  printf("\033[1;31m\n\nWHAT DO YOU WANT TO DO NOW?\n\n\033[0m");
  printf("\033[1;37m1) STORE INFORMATION.\n\n2) RETURN HOME.\n\n\033[1;31m3) EXIT.\n\n\033[0;32mCHOICE: ");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");

  if(choice == 1){
    storeInformation(username);
  }
  else if(choice == 2){
    main();
  }
  else if(choice == 3){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}
