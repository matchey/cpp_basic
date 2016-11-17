//show income and expenditure from bowling score
#include<iostream>
#include<string>
#include<cstdlib>
#include<map>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<time.h>

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

using namespace std;

ofstream wfile;

class Player
{
	string name;//player name
	int points;//player's latest score
	int team;//player's team
	float income_expenditure;//income and expenditure
	float average; //player's score average(include handicap)
	int sum; //player's score sum
	public:
	Player(){ points = 0; sum = 0; income_expenditure=0; average=0;};
	string get_name(){return name;};
	int get_points(){return points;};
	int get_team(){return team;};
	float get_ave(){return average;};
	int get_sum(){return sum;};
	void set_name(string x){ name = x; };
	void set_team(int x){ team = x;};
	void set_team_manual();
	void add_income_expenditure(int x){ income_expenditure += x; };
	void add_point(int x){ points += x; };
	void add_sum(int x){ sum += x; };
	int input_point();
	void show_score() const;
	void show_income_expenditure() const;
	void show_ave() const;
	float calc_ave(int);
};

void Player::set_team_manual()/*{{{*/
{
	cout<<"Type "<<name<<"'s team number: ";
	while(1){
		for(cin>>team;!cin;cin>>team){
			cin.clear();
			cin.ignore();
		}
		if(!(team<0||team>20)){
			break;
		}else{
			cout<<"team number must be in 0~20"<<endl;
			cout<<"Type team number(0~20):";
			team=0;
		}
	}
}/*}}}*/

int Player::input_point()/*{{{*/
{
	cout<<"Type "<<name<<"'s score : ";
	while(1){
		for(cin>>points;!cin;cin>>points){
			cin.clear();
			cin.ignore();
		}
		if(!(points<0||points>300)){
			break;
		}else{
			cout<<"score must be in 0~300"<<endl;
			cout<<"Type score(0~300):";
			points=0;
		}
	}
	return points;
}/*}}}*/

void Player::show_score() const/*{{{*/
{
	cout<<name<<" has "<<points<<" points"<<endl;
}/*}}}*/

void Player::show_income_expenditure() const/*{{{*/
{
	cout<<name<<": ";
	printf("%5d yen\n", (int)income_expenditure);
}/*}}}*/

void Player::show_ave() const/*{{{*/
{
	cout<<name<<"'s average: ";
	printf("%4.1f\n", average);
}/*}}}*/

float Player::calc_ave(int count)/*{{{*/
{
	average = ((count -1.0 ) * average + points) / count;
	return average;
}/*}}}*/

bool check_mkdir()/*{{{*/
{
	char n[2];
	bool rtn = true;
	cout<<"./record/ directory exist?  [Y/n]";
	scanf("%[^\n]",n);
	if(*n=='n'){
		cout<<"try again after type terminal command \"mkdir record\""<<endl;
		rtn = false;
	}else{
		rtn = true;
		time_t now = time(NULL);
		struct tm *pnow = localtime(&now);
		int year = pnow->tm_year+1900;
		int month = pnow->tm_mon + 1;
		int day = pnow->tm_mday;
		int hour = pnow->tm_hour;
		int min = pnow->tm_min;
		
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
		
		// cout<<fname<<endl;
		wfile.open(fname.c_str());
	}
	*n = '\n';
	return rtn;
}/*}}}*/

int set_player_num()/*{{{*/
{
	int num = 1;
	cout<<"input number of players: ";
	while(1){
		for(cin>>num;!cin;cin>>num){
			cin.clear();
			cin.ignore();
		}
		if(!(num<1||num>20)){
			break;
		}else{
			cout<<"number of players must be in 1~20"<<endl;
			cout<<"Type number of players(1~20):";
			num=1;
		}
	}
	return num;
}/*}}}*/

void set_each_name(int num, Player *player)/*{{{*/
{
	string tmp;
	for(int i;i<num;i++){
		cout<<"type player"<<i+1<<"'s name: ";
		cin>>tmp;
		player[i].set_name(tmp);
		cin.clear();
		cin.ignore();
	}
}/*}}}*/

template<class T> void shuffle(T ary[], int size)/*{{{*/
{
	int j = 0;
	T t;
	srand((unsigned int)time(NULL));
	for(int i=0; i<size; i++){
		j = rand()%size;
		t = ary[i];
		ary[i] = ary[j];
		ary[j] = t;
	}
}/*}}}*/

template<class KEY, class VALUE> void my_sort(KEY key[], int size, VALUE value[], bool reverse)/*{{{*/
{
	KEY k;
	VALUE v;
	int sign = reverse ? 1:-1; //true:DESCENDING, false:ASCENDING;
	for(int i=0; i<size; i++){
		for(int j=i; j<size; j++){
			if(sign * value[i] < sign * value[j]){
				k = key[i];
				v = value[i];

				key[i] = key[j];
				value[i] = value[j];

				key[j] = k;
				value[j] = v;
			}
		}
	}
}/*}}}*/

void set_team_auto(int num, Player *player)/*{{{*/
{
	int team_num=1;//number of teams
	if(num > 1){
		cout<<"Type a number of teams: ";
		while(1){
			for(cin>>team_num;!cin;cin>>team_num){
				cin.clear();
				cin.ignore();
			}
			if(!(team_num<0||team_num>num)){
				break;
			}else{
				cout<<"team number must be in 0~"<<num<<endl;
				cout<<"Type number(0~"<<num<<"):";
				team_num=2;
			}
		}
	}
	int team = 1;
	int each_num = num / team_num;
	for(int i=0;i<team_num;i++){
		printf("team%d:         ",i+1);
	}
	cout<<endl;
	shuffle<Player>(player, num);
	for(int i=0;i<num;i++){
		player[i].set_team(team);
		printf("%-15s",player[i].get_name().c_str());
		team += 1;
		if(team > team_num){
			cout<<endl;
			team = 1;
		}
	}
	cout<<endl;
}/*}}}*/

void set_team_select(int num, Player *player)/*{{{*/
{
	int select_mode = 1;
	if(num > 1){
		cout<<"team set  AUTO:1   or   MANUAL:2 "<<endl;
		cout<<"select: ";
		while(1){
			for(cin>>select_mode;!cin;cin>>select_mode){
				cin.clear();
				cin.ignore();
			}
			if(!(select_mode<1||select_mode>2)){
				break;
			}else{
				cout<<"select 1 or 2"<<endl;
				cout<<"Type mode(1~2):";
				select_mode=1;
			}
		}
	}
	switch(select_mode){
		case 1:
			set_team_auto(num, player);
			break;
		case 2:
			for(int i=0;i<num;i++){
				player[i].set_team_manual();
			}
			cout<<endl;
			break;
		default:
			set_team_auto(num, player);
			cout<<"error"<<endl;
			break;
	};
}/*}}}*/

int set_rate(int base_rate)/*{{{*/
{
	int rate = base_rate;
	bool flag = false;
	srand((unsigned int)time(NULL));
	if(rand()%10<3){
		flag = true;
	}
	if(flag){
		rate *= rand()%2+1;
	}
	return rate;
}/*}}}*/

int change_rate()/*{{{*/
{
	int rate = 1;
	cout<<"input rate: ";
	while(1){
		for(cin>>rate;!cin;cin>>rate){
			cin.clear();
			cin.ignore();
		}
		if(!(rate<1||rate>100)){
			break;
		}else{
			cout<<"rate must be in 1~100"<<endl;
			cout<<"Type number of rate(1~100):";
			rate=1;
		}
	}
	return rate;
}/*}}}*/

typedef pair<int, int> ass_arr;/*{{{*/
bool sort_less(const ass_arr& left,const ass_arr& right){
	return left.second < right.second;
}
bool sort_greater(const ass_arr& left,const ass_arr& right){
	return left.second > right.second;
}/*}}}*/

class Inout/*{{{*/
{
	int num; //number of players
	int player_points[20]; //for one game
	int handicap[20]; //for one game
	Player *player;
	map <int, pair<int, int> > team_points; //<"team name", "team score, number of members">
	public:
	Inout(int, Player*);
	bool check(int);
	void set_handi(int);
	void team_calc(int);
	void player_calc(int);
	void calc_handi();
};
Inout::Inout(int num_p, Player *p)/*{{{*/
{
	num = num_p;
	player = p;
}/*}}}*/

vector<int> sort_by_sn(map <int, pair<int, int> > team_points, vector<int> &team_name, int s_n)//score_numOFmem:0_1/*{{{*/
{
	int tmp; //sort swap tempolary
	bool flag = false;
	sort(team_name.begin(),team_name.end()); //sort in ascending order by name ([1]1,[2]2,[0]3,...)
	int len = (int)team_name.size();

	srand((unsigned int)time(NULL));rand();
	
	vector<int> t_name;
	for(int i=0;i<len;i++){t_name.push_back(team_name[i]);}

	for(int i=0;i<len;i++){
	}
	switch(s_n){
		case 0: //sort in ASCENDING order by SCORE
			for(int i=0;i<len;i++){
				flag = false;
				for(int j=len-1;j>i;j--){
					if( team_points[team_name[i]].first >= team_points[team_name[j]].first ){
						flag = true;
						if(team_points[team_name[i]].first == team_points[team_name[j]].first){
							flag = rand() % 2 ? true : false;
						}
					}
					if(flag){
						tmp = t_name[i];  t_name[i] = t_name[j];  t_name[j] = tmp; //swap
					}
				}
			}
			break;
		case 1: //sort in DESCENDING order by NUMBER OF MEMBERS
			for(int i=0;i<len;i++){
				flag = false;
				for(int j=len-1;j>i;j--){
					if( team_points[team_name[i]].second <= team_points[team_name[j]].second ){
						flag = true;
						if(team_points[team_name[i]].second == team_points[team_name[j]].second){
							flag = rand()%2 ? true : false;
						}
					}
					if(flag){
						tmp = t_name[i];  t_name[i] = t_name[j];  t_name[j] = tmp; //swap
					}
				}
			}
			break;
		default:
			cout<<"error"<<endl;
			break;
	};
	for(int i=0;i<len;i++){
		team_name[i] = t_name[i];
	}
	return t_name;
}/*}}}*/

void Inout::set_handi(int count)/*{{{*/
{
	for(int i=0; i<num; i++){ //remove latest score
		player[i].add_point(-player_points[i]);
		team_points[ player[i].get_team() ].first -= player_points[i];
		team_points[ player[i].get_team() ].second -= 1;
	}
	calc_handi();
	for(int i=0; i<num; i++){
		player_points[i] += handicap[i];
		player[i].add_point(player_points[i]);
		team_points[ player[i].get_team() ].first += player_points[i];
		team_points[ player[i].get_team() ].second += 1;
	}
}/*}}}*/

bool Inout::check(int count)/*{{{*/
{
	char n[2];
	bool rtn = true;
	cout<<"OK? (set handicap:[s])  [Y/n] ";
	while(getchar() != '\n') ;
	scanf("%[^\n]",n);
	if(*n=='n'){
		rtn = false;
		for(int i=0; i<num; i++){ //remove latest score
			player[i].add_point(-player_points[i]);
			player[i].add_sum(-player_points[i]);
			team_points[ player[i].get_team() ].first -= player_points[i];
			player_points[i] = 0;
			team_points[ player[i].get_team() ].second -= 1;
		}
	}else if(*n=='s'){
		set_handi(count);
		rtn = true;
	}else{
		rtn = true;
	}
	return rtn;
}/*}}}*/

void Inout::team_calc(int count)/*{{{*/
{
	int sum = 0; //sum points every team
	vector<int> team_name; //soted for num of mem;
	map<int, pair<int, int> >::iterator it;
	map<int, pair<int, int> >::iterator ite;
	int tmp; //sort swap tempolary
	int m = 0; int n = 0;//for loop counter
	bool flag = false;
	while(!flag){
		for(int i=0; i<num; i++){ //set score to each team
			player_points[i] = player[i].input_point();
			player[i].add_sum(player_points[i]);
			team_points[ player[i].get_team() ].first += player_points[i];
			team_points[ player[i].get_team() ].second += 1;
		}
		flag = check(count);
	}
	for(int i=0; i<num; i++){ //set score to each team
		player[i].calc_ave(count);
	}
	for(it=team_points.begin(); it!=team_points.end(); it++){team_name.push_back(it->first);} //set team name
	sort_by_sn(team_points, team_name, 1); //score:0, num of men:1
	int num_teams = (int)team_name.size(); //number of teams
	int num_team_max = team_points[team_name[0]].second;
	float ratio = 1.0; //ratio of members
	for(int i=0; i<num_teams-1; i++){
		ratio = 1.0*num_team_max / team_points[team_name[i+1]].second;
		// ratio = 1.0*team_points[team_name[i]].second / team_points[team_name[i+1]].second;
		team_points[team_name[i+1]].first = int(ratio*team_points[team_name[i+1]].first +0.5);
		sum += team_points[team_name[i]].first;
	}
	sum += team_points[team_name[num_teams-1]].first;
	int ave = sum / num_teams;
	sum = 0;
	for(it=team_points.begin(); it!=team_points.end(); it++){ //calc each team's income and expenditure
		it->second.first -= ave;
		sum += it->second.first;
	}
	sort_by_sn(team_points, team_name, 0); //score:0, num of mem:1
	for(int i=0; i<num_teams-1; i++){
		if(!sum--){break;}
		team_points[team_name[i]].first -= 1;
	}
}/*}}}*/

void Inout::player_calc(int rate)/*{{{*/
{
	int sign = 1;
	int score_abs = 0;
	int player_inout[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //each player's income and expenditure
	map<int, pair<int, int> >::iterator it;
	int n = 0; //use in for loop

	my_sort<Player, int>(player, num, player_points, sign+1);
	for(it=team_points.begin(); it!=team_points.end(); it++){ //calc each player's income and expenditure
		score_abs = it->second.first;
		sign = score_abs < 0 ? -1 : 1;
		score_abs *= sign;
		while( score_abs>0 ){
			for(int i=0; score_abs && i<num ; i++){
				n = sign+1 ? i : num-1-i;
				if( player[n].get_team() == it->first ){
					score_abs -= 1;
					player_inout[n] += sign;
				}
			}
		}
	}
	for(int i=0;i<num;i++){
		player[i].add_income_expenditure(player_inout[i]*rate);
	}
	my_sort<Player, int>(player, num, player_inout, true);
	// for(int i=0;i<num;i++){//last result show
	// 	player[i].show_income_expenditure();
	// }
	for(int i=0;i<num;i++){//last result show
		wfile<<player[i].get_name()<<","<<player_inout[i]*rate<<",,";
	}
	wfile<<endl;
}/*}}}*/

void Inout::calc_handi()/*{{{*/
{
	float ave = 0;
	float max = player[0].get_ave();
	for(int i=1;i<num;i++){
		ave = player[i].get_ave();
		if(max < ave){
			max = ave;
		}
	}
	max = (int)max - (int)max%10;
	for(int i=0; i<num; i++){
		ave = player[i].get_ave();
		ave += (10.0/3.0) * 3;
		ave = (int)ave - (int)ave %10;
		handicap[i] = max - ave;
		handicap[i] = handicap[i]<0 ? 0 : handicap[i];
	}
}/*}}}*/
/*}}}*/

bool select_cntn(int *rate)/*{{{*/
{
	char n[2];
	bool rtn = true;
	cout<<"Continue? (change rate:[c]) [Y/n]";
	while(getchar() != '\n') ;
	scanf("%[^\n]",n);
	if(*n=='n'){
		rtn = false;
	}else if(*n=='c'){
		*rate = change_rate();
		rtn = true;
	}else{
		rtn = true;
	}
	*n = '\n';
	return rtn;
}/*}}}*/

void show_result(int num, Player* player, int count)/*{{{*/
{
	float ave = 0.0;
	for(int i=0;i<num;i++){//show last average
		// player[i].show_ave();
		ave = player[i].get_sum() / (count - 1.0);
		cout<<player[i].get_name()<<"'s average: ";
		printf("%4.1f\n", ave);
	}
	cout<<endl;
	for(int i=0;i<num;i++){//show latest income and expenditure
		player[i].show_income_expenditure();
	}
}/*}}}*/

void execute(int num, Player *player, int rate, int count)/*{{{*/
{
	set_team_select(num, player);
	rate = set_rate(rate);
	cout<<"===== x"<<rate<<" ===="<<endl;
	Inout in_out(num, player);
	in_out.team_calc(count);
	in_out.player_calc(rate);
}/*}}}*/

void spin()
{
	bool start = check_mkdir();
	if(start){
		int num = set_player_num();
		int rate = 10;
		int count = 1;
		bool flag = true;
		Player *player;
		player = new Player[num];
		set_each_name(num, player);
		while(flag){
			execute(num, player, rate, count);
			flag = select_cntn(&rate);
			count++;
		}
		show_result(num, player, count);
		delete [] player;
	}
}

int main()
{
	spin();
	return 0;
}
