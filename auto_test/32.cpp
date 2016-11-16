#include <stdio.h>

int main(void)
{
	for(int i=0;i<10000000;i++){/*sleep*/}
	printf("roslaunch velodyne_points 32e_points.launch\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	for(int i=0;i<100000000;i++){/*sleep*/}
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("[running]\n");
	for(int i=0;i<1000000000;i++){/*sleep*/}
	// printf("[Done]\n");
	for(int i=0;i<100000000;i++){/*sleep*/}
	return 0;
}
