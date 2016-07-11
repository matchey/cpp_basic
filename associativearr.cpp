#include<iostream>
#include<string>
#include<vector>            //<-vector用
#include<algorithm>         //<-sort用
using namespace std;
typedef pair<string, int> ass_arr;
bool sort_less(const ass_arr& left,const ass_arr& right){
    return left.second < right.second;
}
bool sort_greater(const ass_arr& left,const ass_arr& right){
    return left.second > right.second;
}
int main(){
    int n;
    string str;
    vector<pair<string, int> > arr;
    vector<pair<string, int> >::iterator it;
    cin >> n;
    //データ追加部
    while(n--){
        cin >> str;
        arr.push_back(pair<string, int>(str,rand()%10));
    }

    //降順ソート
    sort(arr.begin(),arr.end(),sort_greater);
    it = arr.begin();
    while(it!=arr.end()){
        cout << it->first << " " << it->second << endl;
        it++;
    }

    //昇順ソート
    sort(arr.begin(),arr.end(),sort_less);
    it = arr.begin();
    while(it!=arr.end()){
        cout << it->first << " " << it->second << endl;
        it++;
    }
}
