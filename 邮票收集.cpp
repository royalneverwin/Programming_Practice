#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n, k;
int money[110];
int dp[110][1010];
int main(){
    cin >> n >> k;
    while(n != 0 || k != 0){
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; i++){
            cin >> money[i];
        }
        for(int i = 1; i <= n; i++){
            dp[i][0] = 0;
        }
        for(int i = 1; i <= k; i++){
            if(i % money[1] == 0)
                dp[1][i] = i / money[1];
            else
                dp[1][i] = -1;
        }
        for(int i = 2; i <= n; i++){
            for(int j = 1; j <= k; j++){
                dp[i][j] = 100000;
                for(int use = 0; use <= j / money[i]; use++){
                    if(dp[i-1][j - use * money[i]] != -1)
                        dp[i][j] = min(dp[i][j], use + dp[i-1][j - use * money[i]]);
                }
                if(dp[i][j] == 100000)
                    dp[i][j] = -1;
            }
        }
        int ans = 10000;
        for(int i = 1; i <= n; i++){
            if(dp[i][k] != -1)
                ans = min(ans, dp[i][k]);
        }
        if(ans == 10000)
            cout << -1 << endl;
        else
            cout << ans << endl;
        cin >> n >> k;
    }
}