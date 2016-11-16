#include <stdio.h>

int main(void)
{
	for(int i=0;i<100000000;i++){/*sleep*/}
	printf("rosrun scan_match2 gicp > bfr.csv\n");
	for(int i=0;i<1000000;i++){/*sleep*/}
	for(int i=0;i<1000000;i++){/*sleep*/}
	printf("create .pcd file\n");
	for(int i=0;i<100000;i++){/*sleep*/}
	for(int i=0;i<100000000;i++){/*sleep*/}
	// printf("[Done]\n");
	for(int i=0;i<1000000000;i++){/*sleep*/}
	return 0;
}
