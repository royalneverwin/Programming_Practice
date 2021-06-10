#include <iostream>
#include <set>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;


//动归！！！
int n;
int a[10010];
int b[10010];
int c[10010];
int dp[10010][4]; //dp[i][j]表示第i个状态是j时前i个同学的power之和最大值. j = 0:empty, 1: left, 2: right, 3: both


int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n;
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> c[i];
    }
    dp[1][0] = a[1];
    dp[1][2] = b[1];
    dp[1][1] = dp[1][3] = numeric_limits<int>::min();
    for(int i = 2; i <= n; i++){
        dp[i][0] = max(dp[i-1][2], dp[i-1][3]) + a[i];
        dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + b[i];
        dp[i][2] = max(dp[i-1][2], dp[i-1][3]) + b[i];
        dp[i][3] = max(dp[i-1][0], dp[i-1][1]) + c[i];
    }
    cout << max(dp[n][0], dp[n][1]) << endl;
    return 0;
}