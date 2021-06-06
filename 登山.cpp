#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;


int n;
int height[1010];
int dp[1010][1010]; //dp[i][j]代表第i个景点为最高峰，第j个景点为最后一个景点时观赏景点最多的数量
int dpPre[1010]; //单增

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n;
    memset(dp, 0, sizeof(dp));
    int maxDP = 0;
    for(int i = 1; i <= n; i++)
        cin >> height[i];
    for(int i = 1; i <= n; i++){ //先处理dpPre
        dpPre[i] = 1;
        for(int j = 1; j < i; j++){
            if(height[j] < height[i] && dpPre[j] + 1 > dpPre[i])
                dpPre[i] = dpPre[j] + 1;
        }
    }
    for(int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = dpPre[i];
            for(int k = i; k < j; k++){
                if(height[k] > height[j] && dp[i][k] + 1 > dp[i][j]){
                    dp[i][j] = dp[i][k] + 1;
                }
            }
            maxDP = max(maxDP, dp[i][j]);
        }
    }
    cout << maxDP << endl;
    return 0;
}