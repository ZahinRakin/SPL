#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include "header.h"


int main(){
  again:
  printf("\033[1;31mWELCOME TO MASTER PASSWORD\n\n\n\033[0m");
  srand(time(0));
  int choice;
  printf("\033[0;37m1.Create Account.\n\n2.Log In.\033[0m\n\n\033[1;31m3.Exit.\033[0m\n\nChoice: ");
  scanf("%d",&choice);
  printf("\n\n");
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

