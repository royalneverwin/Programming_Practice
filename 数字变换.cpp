#include <iostream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
int dp[100000];
struct String{
    string num;
    int cnt;
    int op2cnt;
    int op3cnt;
    String(string _num, int _cnt, int _op2cnt, int _op3cnt): num(_num), cnt(_cnt), op2cnt(_op2cnt), op3cnt(_op3cnt){}
};
queue <String> qs;
int String2Int(string num){
    int c2num = 0;
    for(int i = 0; i < 5; i++){
        c2num *= 10;
        c2num += num[i] - '0';
    }
    return c2num;
}
void AddNew(const String& tmp){
    string num = tmp.num;
    int cnt = tmp.cnt;
    int op2cnt = tmp.op2cnt;
    int op3cnt = tmp.op3cnt;
    //+1
    if(op2cnt != 0){
        for(int i = 0; i < 5; i++){
            string newS = num;
            newS[i] = (num[i] - '0' + 1) % 10 + '0';
            int newN = String2Int(newS);
            if(dp[newN] == 0 && newN != 12345) {
                dp[newN] = cnt + 1;
                qs.push(String(newS, cnt + 1, op2cnt - 1, op3cnt));
            }
        }
    }
    //x2
    if(op3cnt != 0){
        for(int i = 0; i < 5; i++){
            string newS = num;
            newS[i] = ((num[i] - '0') * 2) % 10 + '0';
            int newN = String2Int(newS);
            if(dp[newN] == 0 && newN != 12345) {
                dp[newN] = cnt + 1;
                qs.push(String(newS, cnt + 1, op2cnt, op3cnt - 1));
            }
        }
    }
    //交换
    for(int i = 0; i < 4; i++){
        for(int j = i+1; j < 5; j++){
            string newS = num;
            newS[i] = num[j];
            newS[j] = num[i];
            int newN = String2Int(newS);
            if(dp[newN] == 0 && newN != 12345) {
                dp[newN] = cnt + 1;
                qs.push(String(newS, cnt + 1, op2cnt, op3cnt));
            }
        }
    }
}
void bfs(){
    qs.push(String("12345", 0, 3, 2));
    while(!qs.empty()){
        String tmp = qs.front();
        qs.pop();
        AddNew(tmp);
    }
}
int main(){
    int n;
    memset(dp, 0, sizeof(dp));
    bfs();
    for(int i = 0; i < 100000; i++){
        if(dp[i] == 0 && i != 12345)
            dp[i] = -1;
    }
    while(cin >> n){
        cout << dp[n] << endl;
    }
    return 0;
}