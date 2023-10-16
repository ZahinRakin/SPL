#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void storeInformation(char* username){
  FILE *fp;
  int choice;
  char *password;
  char password_2[53];
  char websiteAddress[100];
  char emailAddress[80];

  fp = fopen(username,"a");
  if(fp == NULL){
    printf("\033[1;31mFILE CANN'T BE OPENED!\n\n\033[0m");
    exit(1);
  }

  printf("\033[1;37mWEBSITE ADDRESS: \033[0m");
  scanf("%s",websiteAddress);
  getchar();
  printf("\n\n");
  fprintf(fp,"%s\n",websiteAddress);//when neede i will encode here.
 

  printf("\033[1;37mEMAIL ADDRESS: \033[0m");
  scanf("%s",emailAddress);
  getchar();
  printf("\n\n");
  fprintf(fp,"%s\n",emailAddress);//when needed here i will encrypt.

  printf("\033[1;37m1) GENERATE PASSWORD.\n\n2) GIVE PASSWORD.\n\n\033[1;32mCHOICE: \033[0m");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");

  if(choice == 1){
    password = generatePassword(password);
    fprintf(fp,"%s\n",password);
  }
  else if(choice == 2){
    again:
    printf("\033[1;31mREMEMBER TO KEEP PASSWORD WITHIN 6-52 CHARACTER:\033[0m ");
    scanf("%s",password_2);
    printf("\n");

    if(strlen(password_2) < 6 || strlen(password_2) > 52){
      printf("\033[1;31mYOUR PASSWORD LENGTH ISN'T WITHIN 6-52 CHARACTERS.\n\n\033[0m");
      goto again;
    }
    getchar();
    int strength = checkStrength(password_2,strlen(password_2));

    if(!strength){
      goto again;
    }
    else{
      fprintf(fp,"%s\n",password_2);
    }
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
    exit(1);
  }
  fclose(fp);


  printf("\033[1;32mWHAT DO YOU WANT TO DO NOW?\033[1;37m\n\n");
  printf("1) STORE MORE INFORMATION.\n\n2) VIEW YOUR INFORMATION.\n\n3) RETURN HOME.\n\n\033[1;31m4) EXIT.\n\n\033[0;32mCHOICE: \033[0m");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");

  if(choice == 1){
    storeInformation(username);
  }
  else if(choice == 2){
    viewInformation(username);
  }
  else if(choice == 3){
    main();
  }
  else if(choice == 4){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}
