#include <stdio.h>

int main(void)
{
	char n[2];
	scanf("%[n]",  n);
	if(*n=='n'){
		printf("again\n");
	}else{
		printf("ok\n");
	}
}
