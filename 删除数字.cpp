#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;
//动态规划
int dp[1010][1010]; //dp[i][j]表示前i个数删掉j个最多数字匹配
int dis[1010];
int n;
int t;
int num[1010];
int main(){
    cin >> t;
    while(t--){
        memset(dp, 0, sizeof(dp));
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> num[i];
            dis[i] = i - num[i];
        }
        if(dis[1] != 0)
            dp[1][0] = 0;
        else
            dp[1][0] = 1;
        for(int i = 2; i <= n; i++){
            if(dis[i] == 0)
                dp[i][0] = dp[i-1][0] + 1;
            else
                dp[i][0] = dp[i-1][0];
        }
        dp[1][1] = 0;
        for(int i = 2; i <= n; i++){
            for(int j = 1; j <= i; j++){
                if(dis[i] < 0){
                    dp[i][j] = dp[i-1][j-1];
                    if(i-1 >= j)
                        dp[i][j] = max(dp[i][j], dp[i-1][j]);
                }
                else if(dis[i] == 0){
                    dp[i][j] = dp[i-1][j-1];
                    if(i-1 >= j)
                        dp[i][j] = max(dp[i][j], dp[i-1][j]);
                }
                else{
                    if(j == dis[i]){
                        dp[i][j] = dp[i-1][j-1];
                        if(i-1 >= j)
                            dp[i][j] = max(dp[i][j], dp[i-1][j] + 1);
                    }
                    else{
                        dp[i][j] = dp[i-1][j-1];
                        if(i-1 >= j)
                            dp[i][j] = max(dp[i][j], dp[i-1][j]);
                    }
                }
            }
        }
        int ans = 0;
        for(int j = 0; j <= n; j++){
            ans = max(ans, dp[n][j]);
        }
        cout << ans << endl;
    }
    return 0;
}