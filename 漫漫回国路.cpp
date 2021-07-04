#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int N;
int graph[11][11];
int dp[11][11][11];
int main(){
    cin >> n;
    while(n--){
        cin >> N;
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                cin >> graph[i][j];
            }
        }
        if(N == 1) {
            cout << "YES" << endl;
            continue;
        }
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(graph[i][j] != -1)
                    dp[i][j][0] = 1;
                else
                    dp[i][j][0] = 0;
            }
        }
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                for(int k = 1; k <= N; k++){
                    if(dp[j][k][i-1])
                        dp[j][k][i] = 1;
                    else if(dp[j][i][i-1] && dp[i][k][i-1])
                        dp[j][k][i] = 1;
                    else
                        dp[j][k][i] = 0;
                }
            }
        }
        if(dp[1][N][N])
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}