#include <stdio.h>

int main(void)
{
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("cp bfr.csv aft.csv\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("graph_slam3D\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("generate aft.csv\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	for(int i=0;i<1000000000;i++){/*sleep*/}
	return 0;
}
