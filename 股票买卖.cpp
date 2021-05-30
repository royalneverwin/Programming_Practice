#include <iostream>
#include <cstring>
using namespace std;


const int N = 100010;
int sell1[N]; //sell1[i]代表在前i天进行买卖最大值
int sell2[N];//sell2[i]代表在后n-i天进行买卖最大值
int price[N];

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        memset(sell1, 0, sizeof(sell1));
        memset(sell2, 0, sizeof(sell2));
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> price[i];
        }
        sell1[1] = 0;
        int minN = price[1];
        for(int i = 2; i < n; i++){
            minN = min(minN, price[i]); //min代表第i天之前的价格最小值
            sell1[i] = max(sell1[i-1], price[i] - minN); //两种可能，1是第i天没有卖，2是第i天卖了(价格为minN的那天买入)
        }
        sell2[n] = 0;
        int maxN = price[n];
        for(int i = n-1; i > 1; i--){
            maxN = max(maxN, price[i]); //max代表第i天之后的价格最大值
            sell2[i] = max(sell2[i+1], maxN - price[i]); //两种可能，1是第i天没有买，2是第i天买了(价格为maxN的那天卖出)
        }
        int maxPrice = 0;
        for(int i = 1; i < n; i++){
            maxPrice = max(maxPrice, sell1[i] + sell2[i+1]);
        }
        cout << maxPrice << endl;
    }
    return 0;
}