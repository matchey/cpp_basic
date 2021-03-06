//数字を入力して貰いその数字の月が何日まであるかを出力するプログラム
#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class MonthDays/*{{{*/
{
	int month;
	string name[12];
	int days;
	public:
	MonthDays();
	void input();
	int judge();
	int judge2();
	void show() const;
};

MonthDays::MonthDays()/*{{{*/
{
	string tmp[12]={"January","February","March","April",
		"May","June","July","August","September",
		"October","November","December"};
	for(int i=0;i<12;i++){
		name[i]=tmp[i];
	}
}/*}}}*/

void MonthDays::input()/*{{{*/
{
	cout<<"Type a number(1~12):";
	while(1){
		for(cin>>month;!cin;cin>>month){
			cin.clear();
			cin.ignore();
			// cout<<"made a mistake"<<endl;
			// cout<<"Type a number(1~12):";
		}
		if(!(month<1||month>12)){
			break;
		}else{
			cout<<"number must be in 1~12"<<endl;
			cout<<"Type a number(1~12):";
			month=0;
		}
	}
}/*}}}*/

int MonthDays::judge()/*{{{*/
{
	if(month == 4 || month == 6 || month == 9 || month == 11)
		days = 30;
	else if(month == 2){
		int year=0;
		cout<<"Type year:";
		cin>>year;
		if(year<1)cout<<"negative number? haha"<<endl;
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear)  
			days = 29;  
		else  
			days = 28;  
	}
	else  
		days = 31;  
}/*}}}*/

int MonthDays::judge2()/*{{{*/
{
	days=((month!=2) ? 31-abs((int(month-7.5))%2):28);

}/*}}}*/

void MonthDays::show() const/*{{{*/
{
	cout<<name[month-1]<<" has "<<days<<" days."<<endl;
}/*}}}*/
/*}}}*/

void execute()
{
	MonthDays tmp;
	tmp.input();
	tmp.judge();
	tmp.show();
}

int main()
{
	execute();
	return 0;
}
