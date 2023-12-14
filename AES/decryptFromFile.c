#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(){//decryption...
	FILE *fin,*fout;
	if((fin = fopen("text.txt","r")) == NULL){
		printf("some error occered!\n");
		exit(1);
	}

	if((fout = fopen("out.txt","w")) == NULL){
		printf("some error occered!\n");
		exit(1);
	}
	unsigned char key[16];
	printf("Enter key: ");
	scanf("%s",key);
	getchar();
	purifyKey(key);

	unsigned char *output;
	unsigned char line[1000];
	while(fgets(line, sizeof(line), fin)){
		output = invCipher(line, output, key);
		line[0] = '\0';
		bytesToString(output, line);
		hexToString(line, line);
		fprintf(fout, "%s",line);
		
		fprintf(fout, "\n");
		free(output);
	}
	// printf("line = %s\n",line);
	return 0;
}
