#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m;
int dp[110][11]; //dp[i][j]表示j个鸡蛋检验i层次数


int F(int nn, int mm){
    if(dp[nn][mm] != 0)
        return dp[nn][mm];
    /*边界条件*/
    if(mm == 0){
        dp[nn][mm] = 0;
        return 0;
    }
    if(mm == 1) {
        dp[nn][mm] = nn;
        return nn;
    }
    if(nn == 1){
        dp[nn][mm] = 1;
        return 1;
    }
    if(nn == 0){
        dp[nn][mm] = 1;
        return 1;
    }
    int ans = 1 << 30;
    for(int i = 1; i <= nn; i++){ //i表示第一个鸡蛋在第i层扔
        ans = min(max(F(i-1, mm-1), F(nn-i,mm)) + 1, ans);
    }
    dp[nn][mm] = ans;
    return ans;
}


int main(){
    while(cin >> n >> m) {
        memset(dp, 0, sizeof(dp));
        cout << F(n, m) << endl;
    }
    return 0;
}

