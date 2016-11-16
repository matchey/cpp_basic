#include <stdio.h>

int main(void)
{
	for(int i=0;i<10000000;i++){/*sleep*/}
	printf("rosbag play\n");
	printf("[INFO]\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("[running]\n");
	for(int i=0;i<600000000;i++){/*sleep*/}
	printf("[Done]\n");
	for(int i=0;i<1000000000;i++){/*sleep*/}
	return 0;
}
