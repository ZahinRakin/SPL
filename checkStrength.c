#include <stdio.h>

int checkStrength(char* password,int length){
  if(length < 6 || length > 52){
    printf("\033[1;31mYOUR PASSWORD LENGTH ISN'T WITHING 6-52.\n\n\033[0m");
    return -7;
  }
  int count = 0;
  if(length >= 8 && length < 10){
    count++;
  }
  else if(length >= 10 && length < 16){
    count += 2;
  }
  else{
    count += 3;
  }
  for(int i = 0; i < length; i++){
    if(((int)password[i] >= 33 && (int)password[i] <= 47) || ((int)password[i] >= 58 && (int)password[i] <= 64) || ((int)password[i] >= 91 && (int)password[i] <= 96) || ((int)password[i] >= 123 && (int)password[i] <= 126)){
      count++;
      break;
    }
  }
  for(int i = 0; i < length; i++){
    if((int)password[i] >= 48 && (int)password[i] <= 57){
      count++;
      break;
    }
  }
  for(int i = 0; i < length; i++){
    if((int)password[i] >= 65 && (int)password[i] <= 90){
      count++;
      break;
    }
  }
  for(int i = 0; i < length; i++){
    if((int)password[i] >= 97 && (int)password[i] <= 122){
      count++;
      break;
    }
  }
  if(count == 7){
    printf("\x1b[32m");
    printf("Strong\n\n");
    printf("\x1b[0m");
    return 2;
  }
  else if(count >= 5 && count < 7){
    printf("\x1b[33m");
    printf("medium\n\n");
    printf("\x1b[0m");
    return 1;
  }
  else if(count < 5){
    printf("\x1b[31m");
    printf("weak\n\n");
    printf("\x1b[0m");
    return 0;
  }
}
