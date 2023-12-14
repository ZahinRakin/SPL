#include <stdio.h>
#include "rsaheader.h"

int main(){
	primeFiller();
	for(int i = 0; i < MAX; i++){
		if(primeNumbers[i])printf("%d,",i);
	}
	return 0;
}