#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void storeInformation(char* username){
  FILE *fp;
  int choice;
  char *password;
  char takePass[53];
  char websiteAddress[100];
  char emailAddress[80];
  int accountNumber = 1;
  char line[100];
  int lineNumber = 1;

  fp = fopen(username,"r");
  if(fp == NULL){
    printf("\033[1;31mFILE CANN'T BE OPENED!\n\n\033[0m");
    exit(1);
  }
  while(fgets(line,sizeof(line),fp)){
    if(((lineNumber-2)%5 == 0) && atoi(line) != 0){
      accountNumber = atoi(line);
      accountNumber++;
    }
    lineNumber++;
  }

  fclose(fp);
  //this finds out the account number for indexing new accounts.
  printf("\033[1;37mWebsite Address: \033[0m");
  scanf("%s",websiteAddress);
  getchar();
  printf("\n\n");
  //here the website address would be added to the file

  printf("\033[1;37mEmail Address: \033[0m");
  scanf("%s",emailAddress);
  getchar();
  printf("\n\n");
  //here the email address would be added to the file
  //storing password porcess starts form now on.


  printf("\033[1;37m1) Generate Password.\n\n2) Give password.\n\n\033[1;32mchoice: \033[0m");
  scanf("%d",&choice);
  getchar();
  printf("\n\n");

  if(choice == 1){
    password = generatePassword(password);
  }
  else if(choice == 2){
    again:
    printf("\033[1;31mRemember to keep password within 6-52 character:\033[0m ");
    scanf("%s",takePass);
    getchar();
    printf("\n");
    int strength = checkStrength(takePass,strlen(takePass));
    if(strength <= 0){
      goto again;
    }
    else{
      password = takePass;
    }
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
    exit(1);
  }


  //opening the file for storing updated infos.
  fp = fopen(username,"a");
  if(fp == NULL){
    printf("\033[1;31mFILE CANN'T BE OPENED!\n\n\033[0m");
    exit(1);
  }
  //storing account informations..
  fprintf(fp,"%d.\n",accountNumber);
  fprintf(fp,"Wesite address: %s\n",websiteAddress);
  fprintf(fp,"Email Address: %s\n",emailAddress);
  fprintf(fp,"Password: %s\n",password);
  fprintf(fp,"---------------------------------------------------------------------\n");
  fclose(fp);


  printf("\033[1;32mWhat do you want to do now?\033[1;37m\n\n");
  printf("1)Store more information.\n\n2) Return home.\n\n3) View your information.\n\n\033[1;31m4) exit.\n\nchoice: \033[0m");
  
  
  scanf("%d",&choice);
  getchar();
  printf("\n\n");


  if(choice == 1){
    storeInformation(username);//modified
  }
  else if(choice == 2){
    main();
  }
  else if(choice == 3){
    viewInformation(username);//modified
  }
  else if(choice == 4){
    exit(0);
  }
  else{
    printf("\033[1;31mWRONG COMMAND!\n\n\033[0m");
  }
}