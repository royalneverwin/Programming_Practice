#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;


//广搜会超内存，因为1000长度。用dp
//找到每一位前面1的个数和后面0的个数，把1全部变成0和0全部变成1就能得到串，用dp时间复杂度O(n)
int dp[2][1010]; //dp[0][i]表示i之前的1的个数，dp[1][i]表示i之后的0的个数


//bool Check(const string& s){
//    int index;
//    for(index = 0; index < s.length(); index++){
//        if(s[index] == '1')
//            break;
//    }
//    if(index == s.length())
//        return true;
//    for(int i = index; i < s.length(); i++){
//        if(s[i] == '0')
//            return false;
//    }
//    return true;
//}


void DP(const string& s) {
    dp[0][0] = 0;
    dp[1][s.length() - 1] = 0;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i - 1] == '1')
            dp[0][i] = dp[0][i - 1] + 1;
        else
            dp[0][i] = dp[0][i - 1];
        if (s[s.length() - i] == '0')
            dp[1][s.length() - i - 1] = dp[1][s.length() - i] + 1;
        else
            dp[1][s.length() - i - 1] = dp[1][s.length() - i];
    }
    if (s[1] == '0')
        dp[1][0] = dp[1][1] + 1;
    else
        dp[1][0] = dp[1][1];
    if (s[s.length() - 2] == '1')
        dp[0][s.length() - 1] = dp[0][s.length() - 2] + 1;
    else
        dp[0][s.length() - 1] = dp[0][s.length() - 2];
    int ans = s.length();
    for (int i = 0; i < s.length(); i++){
        ans = min(ans, dp[0][i] + dp[1][i]);
    }
    cout << ans << endl;
}


int main(){
    int t;
    cin >> t;
    while(t--){
        memset(dp, 0, sizeof(dp));
        string s;
        cin >> s;
        DP(s);
    }
}