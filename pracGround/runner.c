#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void padding(char* input){
  int length = strlen(input);
	unsigned char padd[16];
  int i;
	int paddLength = 16 - length % 16;
  for(i = 0; i < paddLength; i++){
      padd[i] = ' ';
  }
	padd[i] = '\0';
	strcat(input,padd);//padding done
}


int main(){
  char input[100];
  fgets(input, sizeof(input), stdin);
  if(input[strlen(input)-1] == '\n')
    input[strlen(input)-1] = '\0';
  padding(input);
  printf("%s---%d\n",input, strlen(input));
}