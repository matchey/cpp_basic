#include <iostream>

int main(void)
{
	float handi = 0;
	float o_max = 170.0;
	float o_ave = 159.999;
	
	o_ave += (10.0/3.0) * 3;
	int max = (int)o_max - (int)o_max % 10;
	int a_ave = (int)o_ave - (int)o_ave % 10;
	handi = max - a_ave;
	handi = handi < 0 ? 0 : handi;
	std::cout<<handi<<std::endl;
}
