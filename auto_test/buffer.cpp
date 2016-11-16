#include <stdio.h>

int main(void)
{
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("rosrun scan_match2 buffer\n");
	printf("idx offset = 0\n");
	for(int i=0;i<100000;i++){/*sleep*/}
	printf("bag replay speed = 1.0\n");
	for(int i=0;i<100000;i++){/*sleep*/}
	printf("DIST = 1.0\n");
	for(int i=0;i<100000;i++){/*sleep*/}
	printf("generate buffer\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	// printf("[Done]\n");
	for(int i=0;i<1000000000;i++){/*sleep*/}
	return 0;
}
