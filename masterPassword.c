#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include "header.h"

int main(){
  int choice;

  printf("\033[1;31m\n\nWELCOME TO MASTER PASSWORD\n\n\n\n\033[0m");

  srand(time(0));//this is needed for password generation.
  
  again:
  printf("\033[1;37m1) CREATE AN ACCOUNT.\n\n2) LOG IN.\n\n3) EXIT.\n\nCHOICE : \033[0m");
  scanf("%d",&choice);
  printf("\n\n");//this is to maintain the 2 line break distance after the choice.
  getchar();


  if(choice == 1){
    createAccount();
  }
  else if(choice == 2){
    logIn();
  }
  else if(choice == 3){
    exit(0);
  }
  else {
    printf("\033[1;31mWRONG COMMAND!\033[0m\n\n");
    goto again;
  }
  
  return 0;
}

