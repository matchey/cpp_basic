//関数ポインタを用いて高速化  switchだと上から全部評価していく
#include <iostream>

int func_0(int x,int y)
{
	std::cout<<"case 0"<<std::endl;
	return 0;
}

int func_1(int x,int y)
{
	std::cout<<"case 1"<<std::endl;
	return 0;
}
int func_2(int x,int y)
{
	std::cout<<"case 2"<<std::endl;
	return 0;
}
int func_3(int x,int y)
{
	std::cout<<"case 3"<<std::endl;
	return 0;
}
int func_4(int x,int y)
{
	std::cout<<"case 4"<<std::endl;
	return 0;
}
int func_5(int x,int y)
{
	std::cout<<"case 5"<<std::endl;
	return 0;
}
int func_6(int x,int y)
{
	std::cout<<"case 6"<<std::endl;
	return 0;
}
int func_7(int x,int y)
{
	std::cout<<"case 7"<<std::endl;
	return 0;
}
int func_other(int x,int y)
{
	std::cout<<"case default"<<std::endl;
	return 0;
}

int (*switch_func[])(int x, int y) = {func_0, func_1, func_2, func_3, func_4, func_5, func_6, func_7, func_other};
// int (*switch_func[256])(int x, int y);

int main(void)
{
	int value = 0;
	// for(int i=0;i<256;i++)
	// 	switch_func[i] = &func_other;
	std::cout<<"input case:";
	std::cin>>value;
	value = value > 0 && value<8 ? value : 8;
	switch_func[value](0, 1);
}
