#include <stdlib.h>
#include <time.h>
#include "rsaheader.h"

int main(){
    srand(time(NULL));//it worked so don't touch.
    primeFiller();//it is mandatory for keyGenaration;
    keyGenerator();
    char input[1000] = "zahin abdullah rakin\nzahin abdullah rakin\nhello world.";
    char output[1000];
    long encoded[1000];
    long e,n,d;
	printf("{n,e,d} = ");
	scanf("%ld%ld%ld",&n,&e,&d);
	getchar();

    encoder(input, encoded, n, e);
    printf("encrypt: \n");
    for(int i = 0; i < strlen(input); i++){
        printf("%c = %ld\n",input[i],encoded[i]);
    }
    printf("decrypt: \n");
    decoder(encoded, strlen(input),output,n,d);
    output[strlen(input)] = '\0';
    printf("%s...",output);
    return 0;
}