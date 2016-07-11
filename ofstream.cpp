#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<time.h>

using namespace std;

int main(void){
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	int year = pnow->tm_year+1900;
	int month = pnow->tm_mon + 1;
	int day = pnow->tm_mday;
	int hour = pnow->tm_hour;
	int min = pnow->tm_min;
	printf("%2d/%02d/%02d/%02d:%02d\n",
			year,
			month,
			day,
			hour,
			min);
	
	ofstream f;
	ostringstream oss;
	
	oss<<"./record/";
	oss.setf(ios::right); oss.fill('0'); oss.width(2);
	oss<<year;
	oss.setf(ios::right); oss.fill('0'); oss.width(2);
	oss<<month;
	oss.setf(ios::right); oss.fill('0'); oss.width(2);
	oss<<day<<"_";
	oss.setf(ios::right); oss.fill('0'); oss.width(2);
	oss<<hour;
	oss.setf(ios::right); oss.fill('0'); oss.width(2);
	oss<<min<<".csv";
	
	string fname = oss.str();
	
	cout<<fname<<endl;
	f.open(fname.c_str());
	
	return 0;
}
