//bowling scoreから賭けのプラスマイナスを表示するプログラム
#include<iostream>
#include<string>
#include<cstdlib>
#include<map>
#include<vector>
#include<algorithm>

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

using namespace std;

class Player
{
	string name;//player name
	int points;//player's total points
	int team;//player's team
	float income_expenditure;//income and expenditure
	public:
	Player(){ points = 0; };
	string get_name(){return name;};
	int get_points(){return points;};
	int get_team(){return team;};
	void set_name(string x){ name = x; };
	void set_team(int x){ team = x;};
	void set_team_manual();
	void add_income_expenditure(int x){ income_expenditure += x; };
	void add_point(int x){ points += x; };
	int input_point();
	void show_score() const;
	void show_income_expenditure() const;
};

void Player::set_team_manual()/*{{{*/
{
	cout<<"Type "<<name<<"'s team number: ";
	while(1){
		for(cin>>team;!cin;cin>>team){
			cin.clear();
			cin.ignore();
		}
		if(!(team<0||team>8)){
			break;
		}else{
			cout<<"team number must be in 0~8"<<endl;
			cout<<"Type team number(0~8):";
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
	printf("%5d yen\n",int(income_expenditure));
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
		if(!(num<1||num>8)){
			break;
		}else{
			cout<<"number of players must be in 1~8"<<endl;
			cout<<"Type number of players(1~8):";
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
	int team_num=2;//number of teams
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
		rate *= rand()%3+1;
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
	int player_points[8]; //for one game
	Player *player;
	map <int, pair<int, int> > team_points; //<"team name", "team score, number of members">
	public:
	Inout(int, Player*);
	bool check(Player*);
	void team_calc();
	void player_calc(int);
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

bool Inout::check(Player *player)/*{{{*/
{
	char n[2];
	bool rtn = true;
	cout<<"OK? [Y/n] ";
	while(getchar() != '\n') ;
	scanf("%[^\n]",n);
	if(*n=='n'){
		rtn = false;
		for(int i=0; i<num; i++){ //set score to each team
			player[i].add_point(-player_points[i]);
			team_points[ player[i].get_team() ].first -= player_points[i];
			player_points[i] = 0;
			team_points[ player[i].get_team() ].second -= 1;
		}
	}else{
		rtn = true;
	}
	return rtn;
}/*}}}*/

void Inout::team_calc()/*{{{*/
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
			team_points[ player[i].get_team() ].first += player_points[i];
			team_points[ player[i].get_team() ].second += 1;
		}
		flag = check(player);
	}
	for(it=team_points.begin(); it!=team_points.end(); it++){team_name.push_back(it->first);} //set team name
	sort_by_sn(team_points, team_name, 1); //score:0, num of men:1
	int num_teams = (int)team_name.size(); //number of teams
	float ratio = 1.0; //ratio of members
	for(int i=0; i<num_teams-1; i++){
		ratio = 1.0*team_points[team_name[i]].second / team_points[team_name[i+1]].second;
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
	int player_inout[] = {0,0,0,0,0,0,0,0}; //each player's income and expenditure
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
}/*}}}*/
/*}}}*/

bool select_cntn()/*{{{*/
{
	char n[2];
	bool rtn = true;
	cout<<"Continue? [Y/n] ";
	while(getchar() != '\n') ;
	scanf("%[^\n]",n);
	if(*n=='n'){
		rtn = false;
	}else{
		rtn = true;
	}
	return rtn;
}/*}}}*/

void execute(int num, Player *player, int rate)/*{{{*/
{
	set_team_select(num, player);
	rate = set_rate(rate);
	cout<<"===== x"<<rate<<" ===="<<endl;
	Inout in_out(num, player);
	in_out.team_calc();
	in_out.player_calc(rate);
}/*}}}*/

void spin()
{
	int num = set_player_num();
	int rate = 10;
	bool flag = true;
	Player *player;
	player = new Player[num];
	set_each_name(num, player);
	while(flag){
		execute(num, player, rate);
		flag = select_cntn();
	}
	for(int i=0;i<num;i++){//last result show
		player[i].show_income_expenditure();
	}
	delete [] player;
}

int main()
{
	spin();
	return 0;
}
