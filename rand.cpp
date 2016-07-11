#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(void)

{
	srand((unsigned int)time(NULL));rand();rand();rand();rand();
	for(int i=0;i<10;i++){
		cout<<rand()%2<<endl;
	}
	return 0;
}
