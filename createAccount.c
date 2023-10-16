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

  printf("\033[1;37m1) GENERATE PASSWORD.\n\n2) GIVE PASSWORD.\n\n3) EXIT.\n\n\033[0;31m(character:6-52)\n\n\033[0;37mCHOICE: \033[0m");
  scanf("%d",&choice);
  printf("\n");
  getchar();

  if(choice == 1){
    password = generatePassword(password);

    printf("\033[1;37mHERE IS YOUR PASSWORD: \033[1;30m");
    printf("%s",password);
    printf("\033[0m");

    //file creation
    fp = fopen(username, "a"); //MODE A MOST PROBABLY WILL SATISFY MY HUNGER.
    if(fp == NULL){
      printf("ERROR WHILE OPEING THE FILE!\n");
      exit(1);
    }

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
      //file creation
      fp = fopen(username, "a");//most probably a+ mode is not necessary.
      if(fp == NULL){
        printf("\033[1;31mERROR WHILE OPENING FILE!\n\033[0m\n");
        exit(1);
      }
      fprintf(fp,"%s\n",password_2);
    }
  }
  else if(choice == 3){
    exit(0);
  }
  else {
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
  fclose(fp);
  // keyGenerate(username);//this need the keygenerate file.
  main();
} 
