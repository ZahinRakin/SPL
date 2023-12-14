#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(){//encryption....
	char input[1000];
	char input2[1000];
	unsigned char* output;
	unsigned char key[16];
	printf("Enter key: ");
	scanf("%s",key);
	getchar();
	purifyKey(key);
	//key secured.
	printf("Enter input: ");
	scanf("%s",input);
	output = cipher(input, output, key);

	printf("encrypt:\n");
	for(int j = 0; j < strlen(input); j++){
		printf("%02x ",output[j]);
		if(j == 15)
			printf("\n");
	}
	printf("\n\n");
	hexToString(*output, input2);
	printf("hex to str: %s\n",input2);
	
	output = invCipher(input2, output, key);

	printf("decrypt:\n");
	for(int j = 0; j < strlen(input); j++){
		printf("%02x ",output[j]);
		if(j == 15)
			printf("\n");
	}
	printf("\n\n");
	
	
    
	return 0;
}
