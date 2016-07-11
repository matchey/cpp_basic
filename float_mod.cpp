#include <iostream>

int main(void)
{
	float handi = 0;
	float o_max = 9.999;
	float o_ave = 1.0;
	
	o_ave += (10.0/3.0) * 3;
	int max = (int)o_max - (int)o_max % 10;
	int a_ave = (int)o_ave - (int)o_ave % 10;
	handi = max - a_ave;
	handi = handi < 0 ? 0 : handi;
	std::cout<<handi<<std::endl;

	std::cout<<1%10;
}
